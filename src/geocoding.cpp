#include "../include/geocoding.h"

using std::string;

geoCoding::geoCoding() = default;
const string workersURL = "https://geocoding.pixelion.workers.dev/";
const string backupURL = "https://ipapi.co/json/";

struct geoData geoCoding::workersAPI() {
  cpr::Response res = cpr::Get(cpr::Url{workersURL});
  struct geoData data{};
  if (res.status_code == 200) {
	QJsonDocument jsonRes = QJsonDocument::fromJson(res.text.c_str());
	data.latitude = jsonRes.object()["lat"].toString().toDouble(); // convert jsonObject to QString then to stdString
	data.longitude = jsonRes.object()["lon"].toString().toDouble();
  } else {
	data = geoCoding::backupAPI();
  }
  return data;
}

struct geoData geoCoding::backupAPI() {
  cpr::Response res = cpr::Get(cpr::Url{backupURL});
  if (res.status_code == 200) {
	QJsonDocument jsonRes = QJsonDocument::fromJson(res.text.c_str());
	double lat = jsonRes.object()["latitude"].toString().toDouble();
	double lon = jsonRes.object()["longitude"].toString().toDouble();
	return {lat, lon};
  } else {
	return {999, 999};
  }
}
