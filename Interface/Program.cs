using Interface;
using Interface.Builder;
using Interface.Staff;

List<IPart> plan = new()
{
    new Basement(),
    new Walls(),
    new Walls(),
    new Walls(),
    new Walls(),
    new Window(),
    new Window(),
    new Window(),
    new Window(),
    new Door(),
    new Roof()
};
List<IWorker> workers = new()
{
    new TeamLead(plan),
    new Worker(),
    new Worker(),
    new Worker(),
    new Worker()
};

Team team = new(workers, plan);
House obj = team.BuildHouse();
Console.ReadLine();