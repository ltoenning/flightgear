// AISwiftAircraft.cpp - Derived AIBase class for swift aircrafts
//
// Copyright (C) 2020 - swift Project Community / Contributors (http://swift-project.org/)
// Written by Lars Toenning <dev@ltoenning.de> started on April 2020.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 2 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

#include "AISwiftAircraft.h"
#include <src/Main/globals.hxx>


FGAISwiftAircraft::FGAISwiftAircraft(const std::string& callsign, const std::string& modelString) : FGAIBase(otStatic, false)
{
    model_path.append(modelString.substr(modelString.find("/Aircraft/")));
    setCallSign(callsign);
    _searchOrder = PREFER_AI;
}
void FGAISwiftAircraft::updatePosition(SGGeod& position, SGVec3<double>& orientation, double groundspeed, bool initPos)
{
    m_initPos = initPos;
    _setLatitude(position.getLatitudeDeg());
    _setLongitude(position.getLongitudeDeg());
    _setAltitude(position.getElevationFt());
    setPitch(orientation.x());
    setBank(orientation.y());
    setHeading(orientation.z());
    setSpeed(groundspeed);

}

void FGAISwiftAircraft::update(double dt)
{
    FGAIBase::update(dt);
    Transform();
}
double FGAISwiftAircraft::getGroundElevation(const SGGeod& pos) const
{
    if(!m_initPos) { return std::numeric_limits<double>::quiet_NaN(); }
    double alt = 0;
    SGGeod posReq;
    posReq.setElevationFt(30000);
    posReq.setLatitudeDeg(pos.getLatitudeDeg());
    posReq.setLongitudeDeg(pos.getLongitudeDeg());
    this->getGroundElevationM(posReq, alt, nullptr);
    //globals->get_scenery()->get_elevation_m(posReq,alt,0,_model.get());
    return alt;
}
FGAISwiftAircraft::~FGAISwiftAircraft() = default;
