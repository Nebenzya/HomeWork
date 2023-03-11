namespace Interface.Builder;


partial class Basement : IPart
{
    public bool IsDone { get; protected set; }

    public void Build() => IsDone = true;
}
