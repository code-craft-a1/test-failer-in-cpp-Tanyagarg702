#include <string>
#include <iostream>
#include <assert.h>

using namespace std;

namespace WeatherSpace
{    
    class IWeatherSensor {
        public:
            virtual double TemperatureInC() const = 0;
            virtual int Precipitation() const = 0;
            virtual int Humidity() const = 0;
            virtual int WindSpeedKMPH() const = 0;
    };
    /// <summary>
    /// This is a stub for a weather sensor. For the sake of testing 
    /// we create a stub that generates weather data and allows us to
    /// test the other parts of this application in isolation
    /// without needing the actual Sensor during development
    /// </summary>
    class SensorStub : public IWeatherSensor {
        double temp;
        int precip;
        int humidity;
        int wind;

        public:
        SensorStub(double t, int p, int h, int w)
            : temp(t), precip(p), humidity(h), wind(w) {}
        int Humidity() const override {
            return humidity;
        }

        int Precipitation() const override {
            return  precip;
        }

        double TemperatureInC() const override {
            return temp;
        }

        int WindSpeedKMPH() const override {
            return wind;
        }
    };
    string Report(const IWeatherSensor& sensor)
    {
        int precipitation = sensor.Precipitation();
        int wind = sensor.WindSpeedKMPH();
        double temp = sensor.TemperatureInC();

        if (precipitation >= 60) {
            if (wind > 50) {
                return "Alert, Stormy with heavy rain";
            }
            return "Rainy Day";
        }

        if (precipitation >= 20 && precipitation < 60 && temp > 25) {
            return "Partly Cloudy";
        }

        return "Sunny Day";
    }
    
    void TestRainy()
    {
        SensorStub sensor(26, 70, 72, 52); 
        string report = Report(sensor);
        cout << "Rainy Test: " << report << endl;
        assert(report.find("rain") != string::npos);
    }

    void TestHighPrecipitation()
    {
        // This instance of stub needs to be different-
        // to give high precipitation (>60) and low wind-speed (<50)
        SensorStub sensor(24, 70, 70, 20);
        string report = Report(sensor);
        cout << "High Precipitation Test: " << report << endl;
        assert(report.find("Rainy Day") != string::npos);
    }
}

void testWeatherReport() {
    cout << "\nWeather report test\n";
    WeatherSpace::TestRainy();
    WeatherSpace::TestHighPrecipitation();
    cout << "All is well (maybe)\n";
}
