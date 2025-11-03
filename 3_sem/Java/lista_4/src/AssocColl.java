public interface AssocColl {
    void set(String k, double v);
    double get(String k);
    boolean search(String k);
    String[] names();

    default String defaultToString() {
        String[] n = names();
        StringBuilder sb = new StringBuilder();
        sb.append("{");
        for (int i = 0; i < n.length; i++) {
            if (i > 0) sb.append(", ");
            try {
                sb.append(n[i]).append("=").append(get(n[i]));
            } catch (Exception e) {
                sb.append(n[i]).append("=<?>");
            }
        }
        sb.append("}");
        return sb.toString();
    }
}
