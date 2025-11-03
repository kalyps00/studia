public interface AssociativeCollection extends Cloneable, AssocColl {
    void del(String k);
    int size();

    // declare clone to indicate deep cloning is expected
    Object clone();

    default String defaultToString() {
        String[] n = names();
        StringBuilder sb = new StringBuilder();
        sb.append("<");
        for (int i = 0; i < n.length; i++) {
            if (i > 0) sb.append("; ");
            try {
                sb.append(n[i]).append(":").append(get(n[i]));
            } catch (Exception e) {
                sb.append(n[i]).append(":" + "<?>");
            }
        }
        sb.append(">");
        return sb.toString();
    }
}
