const Builder = @import("std").build.Builder;

pub fn build(b: *Builder) void {
    const target = b.standardTargetOptions(.{});
    const mode = b.standardReleaseOptions();

    const exe = b.addExecutable("myprogram", "src/main.cpp");
    exe.setTarget(target);
    exe.setBuildMode(mode);
}
