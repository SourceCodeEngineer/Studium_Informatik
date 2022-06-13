package e02;

public class Players {
    private String name;
    private int currentPoints;
    private int wins;
    private int losses;
    private int draws;

    public Players(String name) {
        this.name = name;
        this.currentPoints = 0;
    }

    public int getPoints() {
        return currentPoints;
    }

    public void setPoints(int points) {
        this.currentPoints = points;
    }

    public String getName() {
        return name;
    }

    public int getWins() {
        return wins;
    }

    public void win() {
        this.wins = this.wins + 1;
    }

    public int getLosses() {
        return losses;
    }

    public void loss() {
        this.losses = this.losses + 1;
    }

    public int getDraws() {
        return draws;
    }

    public void draw() {
        this.draws = this.draws +1;
    }


    @Override
    public String toString() {
        return "Players{" +
                "name='" + name + '\'' +
                ", points=" + currentPoints +
                '}';
    }


}
