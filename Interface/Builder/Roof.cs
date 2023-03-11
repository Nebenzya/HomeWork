namespace Interface.Builder;

internal class Roof : IPart
{
    public bool IsDone { get; protected set; }

    public void Build() => IsDone = true;
}
