import os

def count_lines_in_folder(folder_path):
    total_lines = 0

    for root, _, files in os.walk(folder_path):
        for file_name in files:
            file_path = os.path.join(root, file_name)
            try:
                if file_name == "nlohmann-json.hh":
                    continue
                with open(file_path, 'r', encoding='utf-8') as file:
                    total_lines += sum(1 for line in file)
            except Exception as e:
                print(f"Error reading '{file_path}': {str(e)}")

    return total_lines

if __name__ == "__main__":
    folder_path = input("Enter the folder path: ")

    try:
        line_count = count_lines_in_folder(folder_path)
        print(f"Total number of lines in all files in '{folder_path}': {line_count}")
    except FileNotFoundError:
        print("Folder not found. Please provide a valid folder path.")
