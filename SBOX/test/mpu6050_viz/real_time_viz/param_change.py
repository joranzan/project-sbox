'''
MPU 6050 헤더 파일의 ALPHA 값 변경
'''

import re

def change_alpha_value(file_path, new_alpha):
    with open(file_path, 'r', encoding='cp949') as file:
        data = file.read()

    # #define ALPHA -- 찾기
    pattern = r'#define\s+ALPHA\s+(\d+\.\d+)'
    match = re.search(pattern, data)

    if match:
        current_alpha = match.group(1)
        # 값 바꾸기
        new_data = re.sub(pattern, f'#define ALPHA {new_alpha}', data)

        with open(file_path, 'w') as file:
            file.write(new_data)

        print(f"ALPHA value changed from {current_alpha} to {new_alpha}")
    else:
        print("ALPHA value not found in the file")