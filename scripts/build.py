import subprocess
import argparse
import os


def main(args):
    sdk_base = os.getcwd()
    subprocess.run(
        [
            "cmake",
            f"-DSDK_BASE={sdk_base}",
            f"-C {sdk_base}/cmake/preload.cmake",
            f"-DCMAKE_MODULE_PATH={sdk_base}/cmake",
            f"-DCMAKE_TOOLCHAIN_FILE={sdk_base}/cmake/toolchain.cmake",
            f"-S {args.app_dir}",
            f"-B {args.build_dir}",
        ]
    )


if __name__ == "__main__":
    parser = argparse.ArgumentParser()

    parser.add_argument("-a", "--app-dir", type=str, help="path to the application")

    parser.add_argument(
        "-d", "--build-dir", type=str, help="path to the build directory"
    )

    args = parser.parse_args()
    main(args)
