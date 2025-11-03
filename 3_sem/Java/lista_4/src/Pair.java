public class Pair implements Cloneable {
    public final String key;
    private double value;

    private static void validateKey(String k) {
        if (k == null) throw new IllegalArgumentException("key cannot be null");
        if (k.length() == 0) throw new IllegalArgumentException("key cannot be empty");
        if (!k.matches("[a-z]+")) throw new IllegalArgumentException("key must contain only lowercase letters a-z");
    }

    public Pair(String key, double value) {
        validateKey(key);
        this.key = key;
        this.value = value;
    }

    public double get() {
        return value;
    }

    public void set(double value) {
        this.value = value;
    }

    @Override
    public String toString() {
        return key + "=" + value;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (!(obj instanceof Pair)) return false;
        Pair other = (Pair) obj;
        return this.key.equals(other.key);
    }
    @Override
    public Pair clone() {
        try{
           return (Pair)super.clone();
        } catch (CloneNotSupportedException e) {
           return null;
        }
    }
}
