#include "team.h"

// Constructors
Team::Team():
    team_name{"Team"}, stadium_name{"Stadium"}, seat_capacity{98}, location{"Location"}, playing_surface{"Surface"}, league{"League"}, date_opened{1987}, distance_to_center{980}, roof_type{"Roof"}
{ }

Team::Team(string name, string stadium, int capacity, string location, string surface, string league, int date, int distance, string typology, string roof):
    team_name{name}, stadium_name{stadium}, seat_capacity{capacity}, location{location}, playing_surface{surface}, league{league}, date_opened{date}, distance_to_center{distance}, ballpark_typology{typology}, roof_type{roof}
{ }

Team::Team(const Team &t) :
    team_name{t.team_name}, stadium_name{t.stadium_name}, seat_capacity{t.seat_capacity}, location{t.location}, playing_surface{t.playing_surface}, league{t.league}, date_opened{t.date_opened}, distance_to_center{t.distance_to_center}, ballpark_typology{t.ballpark_typology}, roof_type{t.roof_type}
{ }

Team::~Team() { }

// Getter functions
string Team::getName() { return team_name; }
int Team::getCapacity() { return seat_capacity; }
string Team::getLocation() { return location; }
string Team::getSurface() { return playing_surface; }
string Team::getLeague() { return league; }
int Team::getDate() { return date_opened; }
int Team::getDTC() { return distance_to_center; }
string Team::getTypology() { return ballpark_typology; }
string Team::getRoof() { return roof_type; }
