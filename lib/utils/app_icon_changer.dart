import 'package:flutter/services.dart';
import 'package:logging/logging.dart';

class AppIconChanger {
  static const MethodChannel _channel = MethodChannel('change_icon');

  static Future<void> changeIcon(LauncherIcon icon) async {
    try {
      await _channel.invokeMethod('changeIcon', {'iconName': icon.key});
    } on PlatformException catch (e) {
      Logger.root.severe('Failed to change icon: ${e.message}');
    }
  }

  static List<LauncherIcon> get availableIcons => LauncherIcon.values;
}

enum LauncherIcon {
  defaultIcon('DefaultIcon'),
  catIcon('CatIcon'),
  deezerIcon('DeezerBlueIcon');

  final String key;
  const LauncherIcon(this.key);
}
