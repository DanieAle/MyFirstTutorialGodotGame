import os
import shutil
from SCons.Script import *


opts = Variables([],ARGUMENTS)
gxx_path = shutil.which("g++")
mingw_bin = os.path.dirname(gxx_path)
#options
opts.Add(EnumVariable(
    "platform",
    "Target Platform",
    "windows",
    allowed_values=("windows", "linux","android")
))
opts.Add(EnumVariable(
    "arch_android",
    "Target Architecture android",
    "old",
    allowed_values=("old","modern")
))
opts.Add(EnumVariable(
    "target",
    "Build target",
    "debug",
    allowed_values=("debug", "release")
))

opts.Add(BoolVariable(
    "use_mingw",
    "Use MinGW instead of MSVC (Windows only)",
    False
))

opts.Add(PathVariable(
    "godot_headers_path",
    "Path to Godot headers",
    "godot-cpp/godot-headers",
    PathVariable.PathIsDir
))

opts.Add(PathVariable(
    "godot_cpp_path",
    "Path to godot-cpp",
    "godot-cpp",
    PathVariable.PathIsDir
))
opts.Add(PathVariable(
    'target_path', 
    'The path where the lib is installed.', 
    'MyDodge/native/bin/'))
#Environment

env = Environment(variables=opts)
ndk = "E:/androidsdk/ndk/25.2.9519653"
toolchain = ndk + "/toolchains/llvm/prebuilt/windows-x86_64/bin/"
#selection

if env["platform"] == "windows":
    if env["use_mingw"]:
        print("Usando MINGW...")
        env = Environment(
            tools=["mingw","gcc","g++", "gnulink","ar"],
            variables=opts
        )
        opts.Update(env)
    else:
        print("Usando MSVC....")
        env = Environment(variables=opts)
        opts.Update(env)

    if env["target"] == "debug":
        env.Append(CPPDEFINES=["DEBUG_ENABLED"])
        env.Append(CCFLAGS=["-g"])
    else:
        env.Append(CCFLAGS=["-O3"])
    env.Append(LINKFLAGS=[
    "-static-libgcc",
    "-static-libstdc++"
])
    opts.Update(env)
    arch = "64"

if env["platform"] == "android":
    print("Android...")
    selected_tools = ["gcc", "g++", "gnulink", "ar"]
    env = Environment(
        tools=selected_tools,
        CC=toolchain + "clang",
        CXX=toolchain + "clang++",
        LINK=toolchain + "clang++", # IMPORTANTE: El linker debe ser clang++
        AR=toolchain + "llvm-ar",
        AS=toolchain + "llvm-as",
        STRIP=toolchain + "llvm-strip",
        variables=opts,
        ENV={'PATH': os.environ['PATH']}
    )
    env["CCFLAGS"] = [f for f in env["CCFLAGS"] if not f.startswith('/')]
    env['OBJSUFFIX'] = '.os'
    env['SHOBJSUFFIX'] = '.os'
    opts.Update(env)

    if env["arch_android"] == "old":
        android_flags = [
            "--target=armv7a-linux-androideabi29",
            "-march=armv7-a",
            "-mfloat-abi=softfp",
            "-mfpu=vfpv3-d16",
            "-fPIC",
        ]
        arch = "armv7"
    else:
        android_flags = [
            "--target=aarch64-linux-android21",
            "-march=armv8-a",
            "-fPIC",
        ]
        arch = "arm64v8"
    opts.Update(env)
    env["target_path"] += arch
    env.Append(CCFLAGS=android_flags)
    env.Append(LINKFLAGS=android_flags) # El linker también necesita el --target
    env.Append(CCFLAGS=["-std=c++17"])
    if env["target"] == "debug":
        env.Append(CCFLAGS=["-Og", "-g"])
    elif env["target"] == "release":
        env.Append(CCFLAGS=["-O3"])

env.Append(CPPPATH=[
    env["godot_headers_path"],
    os.path.join(env["godot_cpp_path"], "include"),
    os.path.join(env["godot_cpp_path"], "include", "core"),
    os.path.join(env["godot_cpp_path"], "include", "gen"),
])

print("Compilador real en uso: " + str(env.subst('$CC')))

cpp_library = "libgodot-cpp"


cpp_lib = "godot-cpp." + env["platform"] + "." + env["target"] + "." + arch
env.Append(LIBS=[cpp_lib])
env.Append(LIBPATH=[
    os.path.join(env["godot_cpp_path"], "bin")
])
env.Append(CPPDEFINES=["GDNATIVE_ENABLED"])

#files path to compile

sources = Glob("src/*.cpp")

# end file to godot library

library_name = "libgdMyMain"

if env["platform"] == "windows":
    env["target_path"] += 'win64/'
    suffix = ".dll"
    print(mingw_bin)
    env.Install(env["target_path"], os.path.join(mingw_bin, "libwinpthread-1.dll"))
    env.Install("MyDodge/build/win64/", os.path.join(mingw_bin, "libwinpthread-1.dll"))
elif env["platform"] == "linux":
    env["target_path"] += 'x11/'
    suffix = ".so"
elif env["platform"] == "android":
    env["target_path"] += 'android/'
    suffix = ".so"

env.SharedLibrary(
    target=env["target_path"] + library_name,
    source=sources,
    SHLIBSUFFIX=suffix
)

print("Finish")