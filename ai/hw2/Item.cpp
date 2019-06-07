#include <cmath>
#include "Item.h"

Item::Item()
{
    clusterId = -1;
    idx = -1;
}

long double Item::getSepalLength() const
{
    return attributes[0];
}

long double Item::getSepalWidth() const
{
    return attributes[1];
}

long double Item::getPetalLength() const
{
    return attributes[2];
}

long double Item::getPetalWidth() const
{
    return attributes[3];
}

int Item::getClusterId() const
{
    return clusterId;
}


void Item::readNextItem(std::istream &istream)
{
    std::string row, idxStr, type;
    char c;
    std::getline(istream, row);
    if (istream.eof())
        return;

    std::stringstream streamRow(row);

    std::getline(streamRow, idxStr, DEILIMITER);
    idxStr = idxStr.substr(1);
    idxStr = idxStr.erase(idxStr.length() - 1);
    idx = std::stoi(idxStr);

    for (long double & attribute : attributes)
    {
        streamRow >> attribute;
        streamRow >> c;
    }

    //we dont use this just drop it
    streamRow >> type;
}

std::istream &operator>>(std::istream &istream, Item &item)
{
    item.readNextItem(istream);
    return istream;
}

long double Item::euclideanDistance(const std::vector<long double> &centroid)
{
    long double dx, dy, dz, dt;
    dx = (attributes[0] - centroid[0]);
    dx = dx * dx;
    dy = (attributes[1] - centroid[1]);
    dy = dy * dy;
    dz = (attributes[2] - centroid[2]);
    dz = dz * dz;
    dt = (attributes[3] - centroid[3]);
    dt = dt * dt;

    return sqrt((dx + dy + dz + dt));
}

long double Item::manhattanDistance(const std::vector<long double> &centroid)
{
    long double dx, dy, dz, dt;
    dx = std::abs(attributes[0] - centroid[0]);
    dy = std::abs(attributes[1] - centroid[1]);
    dz = std::abs(attributes[2] - centroid[2]);
    dt = std::abs(attributes[3] - centroid[3]);

    return (dx + dy + dz + dt);
}

void Item::setClusterId(int id)
{
    this->clusterId = id;
}

const long double *Item::getAttributes() const
{
    return attributes;
}

bool Item::operator<(const Item &item)
{
    return this->idx < item.idx;
}

long double Item::minkowski3(const std::vector<long double> &centroid)
{
    long double dx, dy, dz, dt;
    dx = (attributes[0] - centroid[0]);
    dx = fabsl(dx * dx * dx*dx);
    dy = (attributes[1] - centroid[1]);
    dy = fabsl(dy * dy * dy*dy);
    dz = (attributes[2] - centroid[2]);
    dz = fabsl(dz * dz * dz*dz);
    dt = (attributes[3] - centroid[3]);
    dt = fabsl(dt * dt * dt*dt);

    return std::pow((dx + dy + dz + dt),1/4.);
}




