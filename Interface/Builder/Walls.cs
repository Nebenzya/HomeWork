namespace Interface.Builder;

internal class Walls : IPart
{
    public bool IsDone { get; protected set; }

    public void Build() => IsDone = true;
}
