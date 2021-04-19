import sys

DEFINER = "#define "
CONNECTOR = "_ON_"
TAIL = " 0x"

colors = {
    "BLACK":"0",
    "BLUE":"1",
    "GREEN":"2",
    "CYAN":"3",
    "RED":"4",
    "PURPLE":"5",
    "BROWN":"6",
    "GRAY":"7",
    "DARK_GRAY":"8",
    "LIGHT_BLUE":"9",
    "LIGHT_GREEN":"a",
    "LIGHT_CYAN":"b",
    "LIGHT_RED":"c",
    "LIGHT_PURPLE":"d",
    "YELLOW":"e",
    "WHITE":"f"
}

def generate():
    result = ""
    for background_color in colors:
        for text_color in colors:
            if background_color != text_color:
                background_code = colors[background_color]
                text_code = colors[text_color]
                result += DEFINER + text_color + CONNECTOR + background_color + TAIL + background_code + text_code + "\n"
    return result

def main():
    print(generate())

if __name__ == "__main__":
    main()
