namespace Interface.Staff;

internal class Worker : IWorker
{
    public void Work(IPart part) => part.Build();
}
