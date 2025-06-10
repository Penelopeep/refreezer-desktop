import collections
import re
import zipfile
import json

lang_crowdin = {
    "ar": "ar-AR",
    "ast": "ast-ES",
    "bg": "bg-BG",
    "cs": "cs-CZ",
    "de": "de-DE",
    "el": "el-GR",
    "es-ES": "es-ES",
    "fa": "fa-IR",
    "fil": "fil-PH",
    "fr": "fr-FR",
    "he": "he-IL",
    "hi": "hi-IN",
    "hr": "hr-HR",
    "hu": "hu-HU",
    "id": "id-ID",
    "it": "it-IT",
    "ko": "ko-KR",
    "nl": "nl-NL",
    "pl": "pl-PL",
    "pt-BR": "pt-BR",
    "ro": "ro-RO",
    "ru": "ru-RU",
    "sk": "sk-SK",
    "sl": "sl-SI",
    "te": "te-IN",
    "tr": "tr-TR",
    "uk": "uk-UA",
    "ur-PK": "ur-PK",
    "uwu": "uwu-UWU",
    "vi": "vi-VN",
    "zh-CN": "zh-CN",
}


def convert_to_single_quotes(json_str):
    def replace_quotes(match):
        key, value = match.groups()
        if "'" in key:
            key = f'"{key}"'
        else:
            key = f"'{key}'"
        if "'" in value:
            value = f'"{value}"'
        else:
            value = f"'{value}'"
        return f"{key}: {value}"

    def replace_locale_quotes(match):
        locale = match.group(1)
        return f"'{locale}': {{"

    pattern = r'"((?:[^"\\]|\\.)*)":\s*"((?:[^"\\]|\\.)*)"'
    single_quote_json = re.sub(pattern, replace_quotes, json_str)

    locale_pattern = r'"(\w+-\w+)":\s*{'
    single_quote_json = re.sub(locale_pattern, replace_locale_quotes, single_quote_json)

    return single_quote_json


# Run `dart fix --apply --code=prefer_single_quotes` in `refreezer\lib\languages\` afterwards
def generate_dart():
    out = {}
    with zipfile.ZipFile("ReFreezer (translations).zip") as zip:
        files = sorted(zip.namelist())
        for file in files:
            if "refreezer.json" in file:
                data = zip.open(file).read().decode("utf-8")
                lang = file.split("/")[0]
                if lang in lang_crowdin:
                    out[lang_crowdin[lang]] = json.loads(
                        data, object_pairs_hook=collections.OrderedDict
                    )

    with open("../lib/languages/crowdin.dart", "w", encoding="utf-8") as f:
        data = json.dumps(out, ensure_ascii=False, indent=2).replace("$", r"\$")
        single_quote_data = convert_to_single_quotes(data)
        out = f"const crowdin = {single_quote_data};"
        f.write(out)


if __name__ == "__main__":
    generate_dart()
