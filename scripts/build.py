import subprocess
import argparse
import os
import pathlib
import shutil


def main(args):
    sdk_base = pathlib.Path(os.getcwd()).as_posix()

    if args.clean:
        try:
            shutil.rmtree(args.build_dir)
        except:
            pass

        if not os.path.exists(os.path.join(args.app_dir, "inc/stm32f7xx_hal_conf.h")):
            shutil.copy(
                os.path.join(
                    sdk_base,
                    "modules/stm32f7xx_hal_driver/Inc/stm32f7xx_hal_conf_template.h",
                ),
                os.path.join(args.app_dir, "inc/stm32f7xx_hal_conf.h"),
            )


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

    if not os.path.exists(os.path.join(args.app_dir, "inc/stm32f7xx_hal_conf.h")):
        shutil.copy(
            os.path.join(
                sdk_base,
                "modules/stm32f7xx_hal_driver/Inc/stm32f7xx_hal_conf_template.h",
            ),
            os.path.join(args.app_dir, "inc/stm32f7xx_hal_conf.h"),
        )


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

    subprocess.run(
        ["cmake", "--build", f"{args.build_dir}", "-j", "8"]
    )


if __name__ == "__main__":
    parser = argparse.ArgumentParser()

    parser.add_argument("-a", "--app-dir", type=str, help="path to the application")

    parser.add_argument(
        "-d", "--build-dir", type=str, help="path to the build directory"
    )

    parser.add_argument(
        "-c",
        "--clean",
        action="store_true",
        help="delete the build directory before building",
    )

    args = parser.parse_args()
    main(args)
