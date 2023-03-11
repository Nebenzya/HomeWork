namespace Interface.Staff;

internal class TeamLead : IWorker
{
    private IEnumerable<IPart> _constructionPlan;

    public TeamLead(IEnumerable<IPart> constructionPlan)
    {
        this._constructionPlan = constructionPlan;
    }

    public void Work(IPart part)
    {
        foreach (var item in _constructionPlan)
        {
            Console.WriteLine($"{item.GetType().Name}. Done = {item.IsDone}");
        }
    }
}
