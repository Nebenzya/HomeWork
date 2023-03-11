namespace Interface.Builder;

internal class Window : IPart
{
    public bool IsDone { get; protected set; }

    public void Build() => IsDone = true;
}
