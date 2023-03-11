namespace Interface.Builder;

internal class House
{
    public bool IsBuild
    {
        get
        {
            foreach (var item in _allParts)
            {
                if (!item.IsDone) return false;
            }
            return true;
        }
    }

    private List<IPart> _allParts;

    public void AddPart(IPart part) => _allParts.Add(part);


}
