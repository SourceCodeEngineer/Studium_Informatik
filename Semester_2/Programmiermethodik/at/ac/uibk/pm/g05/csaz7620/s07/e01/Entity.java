package e01;

import java.util.Objects;

public class Entity<U, T> {
        private final T value;
        private final U key;
        public Entity(T value, U key) {
            this.value = value;
            this.key = key;
        }

    public T getValue() {
            return value;
        }
        public U getKey() {
            return key;
        }

    @Override
    public String toString() {
        return "Entity{" +
                "value=" + value +
                ", key=" + key +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Entity<?, ?> entity = (Entity<?, ?>) o;
        return Objects.equals(key, entity.key);
    }

}

