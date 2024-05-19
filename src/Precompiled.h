#ifndef __PRECOMPILED_H__
#define __PRECOMPILED_H__

#include <vector>
#include <functional>
#include <memory>

// Third Party 
#include <CR/cr.h>
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui_internal.h>
#include <misc/cpp/imgui_stdlib.h>

#include <iostream>
#include <format>
#include <source_location>
#include <filesystem>

#define BEGIN_NS_IMGUI_EDITOR namespace imgui_editor {
#define END_NS_IMGUI_EDITOR }

#if defined(_MSC_VER)
#if defined(__cplusplus)
#define IMGUI_EDITOR_EXPORT extern "C" __declspec(dllexport)
#define IMGUI_EDITOR_IMPORT extern "C" __declspec(dllimport)
#else
#define IMGUI_EDITOR_EXPORT __declspec(dllexport)
#define IMGUI_EDITOR_IMPORT __declspec(dllimport)
#endif
#endif // defined(_MSC_VER)

#if defined(__GNUC__) // clang & gcc
#if defined(__cplusplus)
#define IMGUI_EDITOR_EXPORT extern "C" __attribute__((visibility("default")))
#else
#define IMGUI_EDITOR_EXPORT __attribute__((visibility("default")))
#endif
#define IMGUI_EDITOR_IMPORT
#endif // defined(__GNUC__)

#if defined(__MINGW32__)
#undef IMGUI_EDITOR_EXPORT
#if defined(__cplusplus)
#define IMGUI_EDITOR_EXPORT  extern "C" __declspec(dllexport)
#else
#define IMGUI_EDITOR_EXPORT  __declspec(dllexport)
#endif
#endif

template<typename ... Args>
std::string string_format(const std::string& format, Args ... args)
{
	int size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
	assert(0 < size);
	std::unique_ptr<char[]> buf(new char[size]);
	snprintf(buf.get(), size, format.c_str(), args ...);
	return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

template <typename... Args>
void logImpl(const std::source_location& location, const std::string& formatStr, Args&&... args)
{
	std::cout << string_format(formatStr, args...);
	std::cout << " (";
	std::cout << std::filesystem::path(location.file_name()).filename().string();
	std::cout << ":";
	std::cout << location.line() << ")\n";
}

#define LOG(formatStr, ...) logImpl(std::source_location::current(), formatStr, ##__VA_ARGS__)

#ifdef _MSC_VER

#define debug_break __debugbreak

#else

#ifdef __cplusplus
extern "C" {
#endif

#define DEBUG_BREAK_USE_TRAP_INSTRUCTION 1
#define DEBUG_BREAK_USE_BULTIN_TRAP      2
#define DEBUG_BREAK_USE_SIGTRAP          3

#if defined(__i386__) || defined(__x86_64__)
	#define DEBUG_BREAK_IMPL DEBUG_BREAK_USE_TRAP_INSTRUCTION
__inline__ static void trap_instruction(void)
{
	__asm__ volatile("int $0x03");
}
#elif defined(__thumb__)
	#define DEBUG_BREAK_IMPL DEBUG_BREAK_USE_TRAP_INSTRUCTION
/* FIXME: handle __THUMB_INTERWORK__ */
__attribute__((always_inline))
__inline__ static void trap_instruction(void)
{
	/* See 'arm-linux-tdep.c' in GDB source.
	 * Both instruction sequences below work. */
#if 1
	/* 'eabi_linux_thumb_le_breakpoint' */
	__asm__ volatile(".inst 0xde01");
#else
	/* 'eabi_linux_thumb2_le_breakpoint' */
	__asm__ volatile(".inst.w 0xf7f0a000");
#endif

	/* Known problem:
	 * After a breakpoint hit, can't 'stepi', 'step', or 'continue' in GDB.
	 * 'step' would keep getting stuck on the same instruction.
	 *
	 * Workaround: use the new GDB commands 'debugbreak-step' and
	 * 'debugbreak-continue' that become available
	 * after you source the script from GDB:
	 *
	 * $ gdb -x debugbreak-gdb.py <... USUAL ARGUMENTS ...>
	 *
	 * 'debugbreak-step' would jump over the breakpoint instruction with
	 * roughly equivalent of:
	 * (gdb) set $instruction_len = 2
	 * (gdb) tbreak *($pc + $instruction_len)
	 * (gdb) jump   *($pc + $instruction_len)
	 */
}
#elif defined(__arm__) && !defined(__thumb__)
	#define DEBUG_BREAK_IMPL DEBUG_BREAK_USE_TRAP_INSTRUCTION
__attribute__((always_inline))
__inline__ static void trap_instruction(void)
{
	/* See 'arm-linux-tdep.c' in GDB source,
	 * 'eabi_linux_arm_le_breakpoint' */
	__asm__ volatile(".inst 0xe7f001f0");
	/* Known problem:
	 * Same problem and workaround as Thumb mode */
}
#elif defined(__aarch64__) && defined(__APPLE__)
	#define DEBUG_BREAK_IMPL DEBUG_BREAK_USE_BULTIN_DEBUGTRAP
#elif defined(__aarch64__)
	#define DEBUG_BREAK_IMPL DEBUG_BREAK_USE_TRAP_INSTRUCTION
__attribute__((always_inline))
__inline__ static void trap_instruction(void)
{
	/* See 'aarch64-tdep.c' in GDB source,
	 * 'aarch64_default_breakpoint' */
	__asm__ volatile(".inst 0xd4200000");
}
#elif defined(__powerpc__)
	/* PPC 32 or 64-bit, big or little endian */
	#define DEBUG_BREAK_IMPL DEBUG_BREAK_USE_TRAP_INSTRUCTION
__attribute__((always_inline))
__inline__ static void trap_instruction(void)
{
	/* See 'rs6000-tdep.c' in GDB source,
	 * 'rs6000_breakpoint' */
	__asm__ volatile(".4byte 0x7d821008");

	/* Known problem:
	 * After a breakpoint hit, can't 'stepi', 'step', or 'continue' in GDB.
	 * 'step' stuck on the same instruction ("twge r2,r2").
	 *
	 * The workaround is the same as ARM Thumb mode: use debugbreak-gdb.py
	 * or manually jump over the instruction. */
}
#elif defined(__riscv)
	/* RISC-V 32 or 64-bit, whether the "C" extension
	 * for compressed, 16-bit instructions are supported or not */
	#define DEBUG_BREAK_IMPL DEBUG_BREAK_USE_TRAP_INSTRUCTION
__attribute__((always_inline))
__inline__ static void trap_instruction(void)
{
	/* See 'riscv-tdep.c' in GDB source,
	 * 'riscv_sw_breakpoint_from_kind' */
	__asm__ volatile(".4byte 0x00100073");
}
#else
	#define DEBUG_BREAK_IMPL DEBUG_BREAK_USE_SIGTRAP
#endif


#ifndef DEBUG_BREAK_IMPL
#error "debugbreak.h is not supported on this target"
#elif DEBUG_BREAK_IMPL == DEBUG_BREAK_USE_TRAP_INSTRUCTION
__attribute__((always_inline))
__inline__ static void debug_break(void)
{
	trap_instruction();
}
#elif DEBUG_BREAK_IMPL == DEBUG_BREAK_USE_BULTIN_DEBUGTRAP
__attribute__((always_inline))
__inline__ static void debug_break(void)
{
	__builtin_debugtrap();
}
#elif DEBUG_BREAK_IMPL == DEBUG_BREAK_USE_BULTIN_TRAP
__attribute__((always_inline))
__inline__ static void debug_break(void)
{
	__builtin_trap();
}
#elif DEBUG_BREAK_IMPL == DEBUG_BREAK_USE_SIGTRAP
#include <signal.h>
__attribute__((always_inline))
__inline__ static void debug_break(void)
{
	raise(SIGTRAP);
}
#else
#error "invalid DEBUG_BREAK_IMPL value"
#endif

#ifdef __cplusplus
}
#endif

#endif /* ifdef _MSC_VER */

#endif