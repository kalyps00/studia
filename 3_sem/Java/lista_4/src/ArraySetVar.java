public class ArraySetVar extends SetVar {
    protected Pair[] vars; 
    protected int siz; 

    public ArraySetVar(int capacity) {
        if (capacity < 0) throw new IllegalArgumentException("capacity must be >= 0");
        this.vars = new Pair[capacity];
        this.siz = 0;
    }

    @Override
    public void set(String k, double v) {
        for (int i = 0; i < siz; i++) {
            if (vars[i].key.equals(k)) {
                vars[i].set(v);
                return;
            }
        }
        if (siz >= vars.length) throw new IllegalStateException("no space to add new variable");
        vars[siz++] = new Pair(k, v);
    }

    @Override
    public double get(String k) {
        for (int i = 0; i < siz; i++) {
            if (vars[i].key.equals(k)) 
                return vars[i].get();
        }
        throw new java.util.NoSuchElementException("variable not found: " + k);
    }

    @Override
    public boolean search(String k) {
        for (int i = 0; i < siz; i++) if (vars[i].key.equals(k)) return true;
        return false;
    }

    @Override
    public String[] names() {
        String[] arr = new String[siz];
        for (int i = 0; i < siz; i++) arr[i] = vars[i].key;
        return arr;
    }

    @Override
    public void del(String k) {
        for (int i = 0; i < siz; i++) {
            if (vars[i].key.equals(k)) {
                for (int j = i; j < siz - 1; j++) vars[j] = vars[j + 1];
                vars[--siz] = null;
                return;
            }
        }
    }

    @Override
    public int size() {
        return siz;
    }

    @Override
    public ArraySetVar clone() {
        ArraySetVar copy = new ArraySetVar(this.vars.length);
        copy.siz = this.siz;
        for (int i = 0; i < this.siz; i++) {
            copy.vars[i] = this.vars[i].clone(); 
        }
        return copy;
    }

    @Override
    public void clear() {
        for (int i = 0; i < siz; i++) vars[i] = null;
        siz = 0;
    }

    @Override
    public String toString() {
        return ((AssociativeCollection) this).defaultToString();
    }
}
