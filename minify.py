import re


def minify_cpp_code(input_code):
    # Remove single-line comments
    code = re.sub(r'//.*', '', input_code)

    # Remove multi-line comments
    code = re.sub(r'/\*.*?\*/', '', code, flags=re.DOTALL)

    # Remove leading and trailing whitespace from lines
    code = '\n'.join(line.strip() for line in code.split('\n'))

    # Remove empty lines
    code = '\n'.join(line for line in code.split('\n') if line)

    return code


def minify_cpp_file(input_file_path, output_file_path):
    with open(input_file_path, 'r') as input_file:
        input_code = input_file.read()

        minified_code = minify_cpp_code(input_code)

        output_file_path = output_file_path or input_file_path.replace(
            '.cpp', '.min.cpp')
        with open(output_file_path, 'w') as output_file:
            output_file.write(minified_code)


if __name__ == "__main__":
    input_file_path = "json.hpp"
    output_file_path = "json.min.hpp"

    minify_cpp_file(input_file_path, output_file_path)
    print(f"Minified code written to '{output_file_path}'.")
