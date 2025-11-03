public class PairProb extends Pair {
    private static void checkProb(double v) {
        if (v < 0.0 || v > 1.0) throw new IllegalArgumentException("Probability must be in [0,1]");
    }

    public PairProb(String key, double value) {
        super(key, value);
        checkProb(value);
    }

    @Override
    public void set(double value) {
        checkProb(value);
        super.set(value);
    }
}
