namespace Interface.Builder;

internal class Door : IPart
{
    public bool IsDone { get; protected set; }

    public void Build() => IsDone = true;
}
