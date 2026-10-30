/*
NAME: TSHEPANG MALAKALAKA
COURSE: COS2611
ASSIGNMENT:5
*/

#include <iostream>
#include <vector>
#include <random>
#include <cstdlib>
#include <string>
#include <algorithm>
using namespace std;

//Random seeding
const unsigned int SEED = 2611;
//classes
class Incident{
 public:
    int ID;
    string location;
    string category;
    string severityLevel;
    string status;
    int assignedTeamID;
};

class Location {
    public:
    int ID;
    string area;
};

class ResponseTeam {
public:
int ID;
string location;
string capability;
string status;
};

class roadNetwork{
    public:
    string To;
    string From;
    int time;
};
//graph representation
int getLocationIndex(string name, vector<string>& locationNames)
{
    for (int i = 0; i < locationNames.size(); i++)
    {
        if (locationNames[i] == name)
        {
            return i;
        }
    }
    return -1;
}

//returns the shortest travel time in minutes from sourceIndex to every
//other location, using the hard-coded road network (simple Dijkstra)
vector<int> computeDistances(int sourceIndex, vector<string>& locationNames, vector<roadNetwork>& roads)
{
    int n = locationNames.size();
    vector<int> dist(n, 999999);
    vector<bool> visited(n, false);

    dist[sourceIndex] = 0;

    for (int count = 0; count < n; count++)
    {
        int u = -1;
        int best = 999999;
        for (int i = 0; i < n; i++)
        {
            if (!visited[i] && dist[i] < best)
            {
                best = dist[i];
                u = i;
            }
        }

        if (u == -1)
        {
            break;
        }

        visited[u] = true;

        for (int i = 0; i < roads.size(); i++)
        {
            int a = getLocationIndex(roads[i].From, locationNames);
            int b = getLocationIndex(roads[i].To, locationNames);

            if (a == u && !visited[b] && dist[u] + roads[i].time < dist[b])
            {
                dist[b] = dist[u] + roads[i].time;
            }
            if (b == u && !visited[a] && dist[u] + roads[i].time < dist[a])
            {
                dist[a] = dist[u] + roads[i].time;
            }
        }
    }

    return dist;
}

//random generation
vector<Incident> generateIncidents(vector<string>& locationNames, vector<string>& category, vector<string>& severityLevel)
{
    vector<Incident> incidents;

    for (int i = 0; i < 10; i++)
    {
        Incident incident;
        incident.ID = 1001 + i;
        incident.location = locationNames[rand()%10];
        incident.category = category[rand()%5];
        incident.severityLevel = severityLevel[rand()%3];
        incident.status = "Open";
        incident.assignedTeamID = -1;
        incidents.push_back(incident);
    }

    return incidents;
}

vector<ResponseTeam> generateTeams(vector<string>& locationNames, vector<string>& capability, vector<string>& teamstatus)
{
    vector<ResponseTeam> teams;

    for (int i = 0; i < 6; i++)
    {
        ResponseTeam team;

        team.location = locationNames[rand()%10];
        team.ID = 2001 + i;
        team.capability = capability[rand()%5];

        //requirement: at least 3 teams must start Available
        if (i < 3)
        {
            team.status = "Available";
        }
        else
        {
            team.status = teamstatus[rand()%3];
        }

        teams.push_back(team);
    }

    return teams;
}

//fixed geographic data
vector<Location> buildLocations(vector<string>& locationNames)
{
    vector<Location> locations;

    for (int i = 0; i < 10; i++)
    {
        Location locationObj;
        locationObj.ID = 2011 + i;
        locationObj.area = locationNames[i];
        locations.push_back(locationObj);
    }

    return locations;
}

vector<roadNetwork> buildRoads()
{
    // Real-world data sources:
    // Source 1: Google Maps (maps.google.com) - used to confirm the selected
    //           Gauteng towns exist and to estimate driving times between them.
    // Source 2: AA Route Finder (aa.co.za) - used to cross-check distances and
    //           approximate driving times between the selected locations.
    // Source 3: SANRAL - South African National Roads Agency Limited
    //           (nra.co.za) - used to confirm the national route numbers
    //           (e.g. N1, N12, N14, R28, R82) referenced in the comments below.

    vector<roadNetwork> roads;
    roadNetwork r;

    r.From = "Johannesburg"; r.To = "Sandton";       r.time = 15; roads.push_back(r); //M1
    r.From = "Johannesburg"; r.To = "Soweto";        r.time = 20; roads.push_back(r); //M70/N1
    r.From = "Johannesburg"; r.To = "Krugersdorp";   r.time = 25; roads.push_back(r); //N12
    r.From = "Johannesburg"; r.To = "Benoni";        r.time = 25; roads.push_back(r); //N12
    r.From = "Johannesburg"; r.To = "Walkerville";   r.time = 35; roads.push_back(r); //R82
    r.From = "Johannesburg"; r.To = "Centurion";     r.time = 30; roads.push_back(r); //N1
    r.From = "Sandton";      r.To = "Midrand";       r.time = 15; roads.push_back(r); //N1
    r.From = "Midrand";      r.To = "Centurion";     r.time = 15; roads.push_back(r); //N1
    r.From = "Centurion";    r.To = "Pretoria";      r.time = 10; roads.push_back(r); //N1
    r.From = "Pretoria";     r.To = "Hartbeespoort"; r.time = 40; roads.push_back(r); //R512/R104
    r.From = "Krugersdorp";  r.To = "Hartbeespoort"; r.time = 35; roads.push_back(r); //R560
    r.From = "Krugersdorp";  r.To = "Soweto";        r.time = 25; roads.push_back(r); //R28/R554
    r.From = "Soweto";       r.To = "Walkerville";   r.time = 30; roads.push_back(r); //R82
    r.From = "Benoni";       r.To = "Sandton";       r.time = 35; roads.push_back(r); //N12/R21
    r.From = "Midrand";      r.To = "Pretoria";      r.time = 20; roads.push_back(r); //N1
    r.From = "Sandton";      r.To = "Pretoria";      r.time = 35; roads.push_back(r); //N1
    r.From = "Benoni";       r.To = "Midrand";       r.time = 40; roads.push_back(r); //N12/R21
    r.From = "Pretoria";     r.To = "Krugersdorp";   r.time = 55; roads.push_back(r); //N14/R28

    return roads;
}

//Display functions
void displayIncidents(vector<Incident>& incidents)
{
   for (int i=0; i< incidents.size();++i)
{
cout << "Incidents ID: "<< incidents[i].ID<< endl;
cout << "Location:" << incidents[i].location << endl;
cout <<"Category:" << incidents[i].category << endl;
cout << "Severity:" << incidents[i].severityLevel << endl;
cout <<"Status:" << incidents[i].status << endl;
if (incidents[i].assignedTeamID != -1)
{
cout << "Assigned Team ID:" << incidents[i].assignedTeamID << endl;
}
cout << endl;
}
}

void displayLocationsAndRoads(vector<Location>& locations,vector<roadNetwork>& roads)
{
    for (int i=0; i< locations.size(); i++)
{
    cout << "Locations ID: " << locations[i].ID << endl;
    cout << "Locations area: " << locations[i].area << endl;
    cout << endl;
};

cout << "Road Connections:" << endl;
cout << endl;
for (int i = 0; i < roads.size(); i++)
{
    cout << roads[i].From << " -> " << roads[i].To << " : " << roads[i].time << " min" << endl;
}

}
void displayResponseTeams(vector<ResponseTeam>& teams)
{
for (int i = 0; i < teams.size(); i++)
{
    cout << "Team ID: " << teams[i].ID << endl;
    cout << "Team Location: " << teams[i].location << endl;
    cout << "Team Capability: " << teams[i].capability << endl;
    cout << "Team Status: " << teams[i].status << endl;
    cout << endl;
}
};

//searching
int searchIncidentByID(vector<Incident>& incidents, int searchID)
{
    for (int i = 0; i < incidents.size(); i++)
    {
        if (incidents[i].ID == searchID)
        {
            return i;
        }
    }
    return -1;
}

int searchTeamByID(vector<ResponseTeam>& teams, int searchID)
{
    for (int i = 0; i < teams.size(); i++)
    {
        if (teams[i].ID == searchID)
        {
            return i;
        }
    }
    return -1;
}

//incident prioritisation
int severityScore(string severityLevel)
{
    if (severityLevel == "High")
    {
        return 3;
    }
    else if (severityLevel == "Medium")
    {
        return 2;
    }
    else
    {
        return 1;
    }
}

void prioritiseOpenIncidents(vector<Incident>& incidents)
{
    vector<Incident> openIncidents;

    for (int i = 0; i < incidents.size(); i++)
    {
        if (incidents[i].status == "Open")
        {
            openIncidents.push_back(incidents[i]);
        }
    }

    if (openIncidents.size() == 0)
    {
        cout << "There are no open incidents." << endl;
        return;
    }

    //simple selection sort, highest severity first
    for (int i = 0; i < openIncidents.size() - 1; i++)
    {
        int maxIndex = i;
        for (int j = i + 1; j < openIncidents.size(); j++)
        {
            if (severityScore(openIncidents[j].severityLevel) > severityScore(openIncidents[maxIndex].severityLevel))
            {
                maxIndex = j;
            }
        }
        if (maxIndex != i)
        {
            Incident temp = openIncidents[i];
            openIncidents[i] = openIncidents[maxIndex];
            openIncidents[maxIndex] = temp;
        }
    }

    cout << "Open Incidents, prioritised (highest severity first):" << endl;
    cout << endl;
    for (int i = 0; i < openIncidents.size(); i++)
    {
        cout << "Incident ID: " << openIncidents[i].ID << endl;
        cout << "Location:" << openIncidents[i].location << endl;
        cout << "Category:" << openIncidents[i].category << endl;
        cout << "Severity:" << openIncidents[i].severityLevel << endl;
        cout << endl;
    }
}

//team selection
void investigateIncident(vector<Incident>& incidents, vector<ResponseTeam>& teams, vector<string>& locationNames, vector<roadNetwork>& roads)
{
    int searchID;
    cout << "Enter incident ID: ";
    cin >> searchID;

    int index = searchIncidentByID(incidents, searchID);

    if (index == -1)
    {
        cout << "Incident not found." << endl;
        return;
    }

    cout << endl;
    cout << "Incident ID: " << incidents[index].ID << endl;
    cout << "Location:" << incidents[index].location << endl;
    cout << "Category:" << incidents[index].category << endl;
    cout << "Severity:" << incidents[index].severityLevel << endl;
    cout << "Status:" << incidents[index].status << endl;
    cout << endl;

    vector<ResponseTeam> suitableTeams;

    for (int i = 0; i < teams.size(); i++)
    {
        if (teams[i].capability == incidents[index].category && teams[i].status == "Available")
        {
            suitableTeams.push_back(teams[i]);
        }
    }

    if (suitableTeams.size() == 0)
    {
        cout << "No available team currently has the required capability." << endl;
        return;
    }

    int sourceIndex = getLocationIndex(incidents[index].location, locationNames);
    vector<int> dist = computeDistances(sourceIndex, locationNames, roads);

    //simple selection sort, nearest team first
    for (int i = 0; i < suitableTeams.size() - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < suitableTeams.size(); j++)
        {
            int distJ = dist[getLocationIndex(suitableTeams[j].location, locationNames)];
            int distMin = dist[getLocationIndex(suitableTeams[minIndex].location, locationNames)];
            if (distJ < distMin)
            {
                minIndex = j;
            }
        }
        if (minIndex != i)
        {
            ResponseTeam temp = suitableTeams[i];
            suitableTeams[i] = suitableTeams[minIndex];
            suitableTeams[minIndex] = temp;
        }
    }

    cout << "Suitable available teams (nearest first):" << endl;
    cout << endl;
    for (int i = 0; i < suitableTeams.size(); i++)
    {
        int d = dist[getLocationIndex(suitableTeams[i].location, locationNames)];
        cout << "Team ID: " << suitableTeams[i].ID << endl;
        cout << "Team Location: " << suitableTeams[i].location << endl;
        cout << "Estimated Travel Time: " << d << " minutes" << endl;
        cout << endl;
    }
}

//graph algorithm
void findRoute(vector<string>& locationNames, vector<roadNetwork>& roads)
{
    cout << "Available locations:" << endl;
    for (int i = 0; i < locationNames.size(); i++)
    {
        cout << i << ". " << locationNames[i] << endl;
    }
    cout << endl;

    int fromIndex, toIndex;
    cout << "Enter starting location number: ";
    cin >> fromIndex;
    cout << "Enter destination location number: ";
    cin >> toIndex;

    if (fromIndex < 0 || fromIndex >= locationNames.size() || toIndex < 0 || toIndex >= locationNames.size())
    {
        cout << "Invalid location number." << endl;
        return;
    }

    int n = locationNames.size();
    vector<int> dist(n, 999999);
    vector<int> prev(n, -1);
    vector<bool> visited(n, false);

    dist[fromIndex] = 0;

    for (int count = 0; count < n; count++)
    {
        int u = -1;
        int best = 999999;
        for (int i = 0; i < n; i++)
        {
            if (!visited[i] && dist[i] < best)
            {
                best = dist[i];
                u = i;
            }
        }

        if (u == -1)
        {
            break;
        }

        visited[u] = true;

        for (int i = 0; i < roads.size(); i++)
        {
            int a = getLocationIndex(roads[i].From, locationNames);
            int b = getLocationIndex(roads[i].To, locationNames);

            if (a == u && !visited[b] && dist[u] + roads[i].time < dist[b])
            {
                dist[b] = dist[u] + roads[i].time;
                prev[b] = u;
            }
            if (b == u && !visited[a] && dist[u] + roads[i].time < dist[a])
            {
                dist[a] = dist[u] + roads[i].time;
                prev[a] = u;
            }
        }
    }

    if (dist[toIndex] == 999999)
    {
        cout << "No route found between these locations." << endl;
        return;
    }

    vector<int> path;
    int current = toIndex;
    while (current != -1)
    {
        path.push_back(current);
        current = prev[current];
    }

    cout << endl;
    cout << "Route: ";
    for (int i = path.size() - 1; i >= 0; i--)
    {
        cout << locationNames[path[i]];
        if (i > 0)
        {
            cout << " -> ";
        }
    }
    cout << endl;
    cout << "Total travel time: " << dist[toIndex] << " minutes" << endl;
}

//updating
void updateIncident(vector<Incident>& incidents, vector<ResponseTeam>& teams)
{
    int searchID;
    cout << "Enter incident ID to update: ";
    cin >> searchID;

    int index = searchIncidentByID(incidents, searchID);

    if (index == -1)
    {
        cout << "Incident not found." << endl;
        return;
    }

    if (incidents[index].status == "Open")
    {
        cout << "Suitable available teams:" << endl;
        cout << endl;

        bool anyFound = false;
        for (int i = 0; i < teams.size(); i++)
        {
            if (teams[i].capability == incidents[index].category && teams[i].status == "Available")
            {
                cout << "Team ID: " << teams[i].ID << endl;
                anyFound = true;
            }
        }

        if (!anyFound)
        {
            cout << "No available team with the required capability right now." << endl;
            return;
        }

        int teamID;
        cout << "Enter Team ID to assign: ";
        cin >> teamID;

        int teamIndex = searchTeamByID(teams, teamID);

        if (teamIndex == -1 || teams[teamIndex].capability != incidents[index].category || teams[teamIndex].status != "Available")
        {
            cout << "Invalid choice - team not suitable or not available." << endl;
            return;
        }

        incidents[index].status = "Assigned";
        incidents[index].assignedTeamID = teams[teamIndex].ID;
        teams[teamIndex].status = "Assigned";

        cout << "Incident " << incidents[index].ID << " assigned to Team " << teams[teamIndex].ID << "." << endl;
    }
    else if (incidents[index].status == "Assigned")
    {
        int choice;
        cout << "Mark incident as Resolved? (1 = Yes, 0 = No): ";
        cin >> choice;

        if (choice == 1)
        {
            int teamIndex = searchTeamByID(teams, incidents[index].assignedTeamID);

            incidents[index].status = "Resolved";

            if (teamIndex != -1)
            {
                teams[teamIndex].status = "Available";
            }

            cout << "Incident " << incidents[index].ID << " marked Resolved." << endl;
        }
        else
        {
            cout << "No changes made." << endl;
        }
    }
    else
    {
        cout << "Incident is already Resolved." << endl;
    }
}

void displaySummary(vector<Incident>& incidents, vector<ResponseTeam>& teams)
{
    int open = 0, assigned = 0, resolved = 0;
    for (int i = 0; i < incidents.size(); i++)
    {
        if (incidents[i].status == "Open") open++;
        else if (incidents[i].status == "Assigned") assigned++;
        else resolved++;
    }

    int available = 0, teamAssigned = 0, unavailable = 0;
    for (int i = 0; i < teams.size(); i++)
    {
        if (teams[i].status == "Available") available++;
        else if (teams[i].status == "Assigned") teamAssigned++;
        else unavailable++;
    }

    cout << "Incidents - Open: " << open << ", Assigned: " << assigned << ", Resolved: " << resolved << endl;
    cout << "Teams - Available: " << available << ", Assigned: " << teamAssigned << ", Unavailable: " << unavailable << endl;
}


int main() {

    srand(SEED);

    vector<string>locationNames =
    {
        "Midrand",
        "Soweto",
        "Benoni",
        "Sandton",
        "Krugersdorp",
        "Johannesburg",
        "Pretoria",
        "Centurion",
        "Hartbeespoort",
        "Walkerville"
    };
    vector<string>category =
    {
        "Water",
        "Electricity",
        "Roads",
        "Sanitation",
        "Public Facilities"
    };
vector<string>severityLevel =
{
    "Low",
    "Medium",
    "High"
};

    vector<string> capability =
{
    "Water",
    "Electricity",
    "Roads",
    "Sanitation",
    "Public Facilities"
};
vector<string> teamstatus =
{
    "Available",
    "Assigned",
    "Unavailable"
};

    //generate
    vector<Location> locations = buildLocations(locationNames);
    vector<roadNetwork> roads = buildRoads();
    vector<Incident> incidents = generateIncidents(locationNames, category, severityLevel);
    vector<ResponseTeam> teams = generateTeams(locationNames, capability, teamstatus);

    //Menu
    int choice;

    do
    {

    cout << endl;
    cout << "=========================================" << endl;
    cout << " MUNICIPAL INCIDENT RESPONSE SYSTEM" << endl;
    cout << "=========================================" << endl;
    cout << "1. Display Locations and Roads" << endl;
    cout << "2. Display Incidents " << endl;
    cout << "3. Prioritise Open Incidents " << endl;
    cout << "4. Display Response Team " << endl;
    cout << "5. Investigate Incidents " << endl;
    cout << "6. Find Route " << endl;
    cout << "7. Update Incident " << endl;
    cout << "8. Display Summary " << endl;
    cout << "0. Exit " << endl;
    cout << "Enter your choice: ";

    cin >> choice;

    switch(choice)
    {
        case 1:
        displayLocationsAndRoads(locations, roads);
        break;

        case 2:
        displayIncidents(incidents);
        break;

        case 3:
        prioritiseOpenIncidents(incidents);
        break;

        case 4:
        displayResponseTeams(teams);
        break;

        case 5:
        investigateIncident(incidents, teams, locationNames, roads);
        break;

        case 6:
        findRoute(locationNames, roads);
        break;

        case 7:
        updateIncident(incidents, teams);
        break;

        case 8:
        displaySummary(incidents, teams);
        break;

        case 0:
        cout << "Exiting Municipal Incident Response System." << endl;
        break;

        default:
        cout << "Invalid choice, please try again." << endl;
    }
    }
    while(choice != 0);

    return 0;
}

// ============================================================
// SOLUTION REFLECTION
// ============================================================
//
// I first analysed the problem by breaking it into the main
// information and operations required by the municipal
// operations centre. I identified that the system needed to
// manage locations, roads, incidents and response teams, as
// well as provide functionality for prioritising incidents,
// selecting suitable teams, finding routes and updating
// statuses. I developed and tested each part incrementally
// instead of trying to build the entire program at once.
//
// I decided to represent incidents, locations and response
// teams using separate classes because each represents a
// different type of information in the problem. Incidents
// store information such as their ID, location, category,
// severity, status and assigned team. Response teams store
// their ID, current location, capability and status. Locations
// have an ID and area name. Roads are represented separately
// using a roadNetwork class containing a starting location,
// destination location and travel time.
//
// I used vectors to store collections of these objects because
// the number of incidents and teams is generated at runtime
// and vectors allow the program to store and process multiple
// objects easily. I also used vectors of strings for the fixed
// location names, categories, severity levels, capabilities and
// team statuses. A fixed random seed was used so that the
// program generates data programmatically while still producing
// consistent results when testing.
//
// For incident prioritisation, I first created a separate
// collection containing only incidents whose status was Open.
// This was important because assigned or resolved incidents
// should not be considered when deciding which incidents need
// attention. I converted the severity levels into numerical
// scores, with High having the highest score, and then used
// selection sort to arrange the open incidents from highest to
// lowest severity. I chose this approach because the number of
// incidents is small and it is simple to understand and verify.
//
// When identifying a suitable response team, I compared the
// team's capability with the incident's category and only
// considered teams whose status was Available. After finding
// suitable teams, I used their current locations and the road
// network to determine which team could reach the incident in
// the shortest travel time. This allowed team selection to take
// both capability and location into account rather than simply
// choosing the first matching team.
//
// For route finding, I represented the road network as a
// collection of road connections containing the two connected
// locations and their travel time. I used Dijkstra's algorithm
// to calculate the shortest travel route between two locations.
// The algorithm keeps track of the shortest known travel time
// to each location and updates these values as shorter routes
// are discovered. I also stored the previous location so that
// the actual route could be reconstructed and displayed to the
// user, together with the total travel time.
//
// One of the main design challenges was making sure that the
// different parts of the system worked together correctly.
// For example, assigning an incident must also change the
// response team's status to Assigned, while resolving an
// incident must make the assigned team Available again. Another
// important consideration was ensuring that all road
// connections referred to valid locations and that the network
// was connected well enough for routes to be found.
//
// I tested the program by testing each menu option with
// different incidents, teams and locations. I also tested
// invalid menu choices and invalid location or incident IDs.
// For incident prioritisation, I checked that only Open
// incidents were included and that High severity incidents
// appeared before Medium and Low severity incidents. I tested
// assigning and resolving incidents to make sure both incident
// and team statuses were updated correctly. I also tested route
// finding between different locations and checked that the
// displayed route and total travel time changed appropriately.
//
// Overall, I developed the solution by first understanding the
// problem, choosing representations that matched the real-world
// entities, and then building and testing the required
// functionality incrementally. Testing each section helped me
// identify and correct problems before integrating the complete
// system.
// ============================================================
