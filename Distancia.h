#ifndef AED2324_P12_DISTANCIA_H
#define AED2324_P12_DISTANCIA_H

#include <cmath>

class Distancia {
public:
    double latitude;
    double longitude;

    Distancia(double lat, double lon) : latitude(lat), longitude(lon) {}
};

/* Function to calculate the Haversine distance between two GeoCoordinates
*  Time complexity: O(1)
*/
double haversineDistance(const Distancia& coord1, const Distancia& coord2) {
    // Earth radius in kilometers
    const double earthRadius = 6371.0;

    // Convert latitude and longitude from degrees to radians
    double lat1 = coord1.latitude * M_PI / 180.0;
    double lon1 = coord1.longitude * M_PI / 180.0;
    double lat2 = coord2.latitude * M_PI / 180.0;
    double lon2 = coord2.longitude * M_PI / 180.0;

    // Haversine formula
    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;

    double a = sin(dlat / 2) * sin(dlat / 2) +
               cos(lat1) * cos(lat2) * sin(dlon / 2) * sin(dlon / 2);

    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    // Calculate the distance
    double distance = earthRadius * c;

    return distance;
}

#endif //AED2324_P12_DISTANCIA_H
