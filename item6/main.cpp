class NoCopy {
    public:
        NoCopy()
        {
        }
        ~NoCopy()
        {
        }

        NoCopy(const NoCopy&) = delete;
        NoCopy& operator=(const NoCopy&) = delete;

    private:
};

class OldNoCopy
{
public:
    NoCopy()
    {
    }
    ~NoCopy()
    {
    }

private:
    NoCopy(const NoCopy&);
    NoCopy& operator=(const NoCopy&);
};
int main()
{
    NoCopy nc;
    NoCopy copy = nc;
}
