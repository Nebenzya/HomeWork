using Interface.Builder;

namespace Interface.Staff;

internal class Team
{
    public bool IsBuild
    {
        get
        {
            foreach (var item in _constructionPlan)
            {
                if (!item.IsDone) return false;
            }
            return true;
        }
    }
    private IEnumerable<IWorker> _workers;
    private IEnumerable<IPart> _constructionPlan;

    public Team(IEnumerable<IWorker> workers, IEnumerable<IPart> _constructionPlan)
    {
        this._workers = workers;
        this._constructionPlan = _constructionPlan;
    }

    public House BuildHouse()
    {
        House house = new();
        while (!IsBuild)
        {
            var worker = _workers.ElementAt(new Random().Next(_workers.Count()));
            var unfinishPart = GetUnfinishedPart();
            worker.Work(unfinishPart);
            house.AddPart(unfinishPart);
        }
        return house;
    }

    private IPart GetUnfinishedPart()
    {
        foreach (var item in _constructionPlan)
        {
            if (!item.IsDone) return item;
        }

        return null;
    }
}
