import argparse
import json

def main(args):
    with open(args.sequence_file, "r") as f:
        data = json.load(f)

    sequence_length = len(data["steps"])

    steps = ""
    for step in data["steps"]:
        type = step["type"]
        channel = step["channel"]
        note = step["note"]
        velocity = step["velocity"]

        glide = 0 if step["glide"] == False else 1

        step_string = "{"
        step_string += f"{type},{channel},{note},{velocity},{glide}"
        step_string += "},\n"
        steps += step_string

    output_string = """#ifndef _SEQUENCE_H
#define _SEQUENCE_H
#include \"midi.h\"
"""

    output_string += f"#define SEQUENCE_LENGTH {sequence_length}\n"

    output_string += """MIDIPacket_TypeDef midi_sequence[] = {
"""
    output_string += steps

    output_string += """};
#endif
"""

    with open(args.output, "w") as f:
        f.write(output_string)

if __name__ == "__main__":
    parser = argparse.ArgumentParser()

    parser.add_argument(
        "-f",
        "--sequence-file",
        type=str
    )

    parser.add_argument(
        "-o",
        "--output",
        type=str
    )

    args = parser.parse_args()

    main(args)