import 'package:flutter/material.dart';
import 'package:i18n_extension/i18n_extension.dart';

import '../languages/crowdin.dart';
import '../languages/en_us.dart';

List<Language> languages = [
  Language('en', 'US', 'English'),
  Language('ar', 'AR', 'Arabic'),
  Language('ast', 'ES', 'Asturian'),
  Language('bg', 'BG', 'Bulgarian'),
  Language('cs', 'CZ', 'Czech'),
  Language('de', 'DE', 'German'),
  Language('el', 'GR', 'Greek'),
  Language('es', 'ES', 'Spanish'),
  Language('fa', 'IR', 'Persian'),
  Language('fil', 'PH', 'Filipino'),
  Language('fr', 'FR', 'Baguette'),
  Language('he', 'IL', 'Hebrew'),
  Language('hi', 'IN', 'Hindi'),
  Language('hr', 'HR', 'Croatian'),
  Language('hu', 'HU', 'Hungarian'),
  Language('id', 'ID', 'Indonesian'),
  Language('it', 'IT', 'Italian'),
  Language('ko', 'KR', 'Korean'),
  Language('nl', 'NL', 'Dutch'),
  Language('pl', 'PL', 'Polish'),
  Language('pt', 'BR', 'Brazil'),
  Language('ro', 'RO', 'Romanian'),
  Language('ru', 'RU', 'Russian'),
  Language('sk', 'SK', 'Slovak'),
  Language('sl', 'SI', 'Slovenian'),
  Language('te', 'IN', 'Telugu'),
  Language('tr', 'TR', 'Turkish'),
  Language('uk', 'UA', 'Ukrainian'),
  Language('ur', 'PK', 'Urdu'),
  Language('uwu', 'UWU', 'Furry'),
  Language('vi', 'VN', 'Vietnamese'),
  Language('zh', 'CN', 'Chinese'),
];
List<Locale> get supportedLocales => languages.map((l) => l.getLocale).toList();

extension Localization on String {
  static final _t = Translations.byLocale('en-US') + language_en_us + crowdin;

  String get i18n => localize(this, _t);
}

class Language {
  String name;
  String locale;
  String country;
  Language(this.locale, this.country, this.name);

  Locale get getLocale => Locale(locale, country);
}
