package edu.utsa.cs3443.tro893_lab5.model;

import java.util.ArrayList;
import android.content.Context;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.List;

public class Act {
    private int actNumber;
    private List<Scene> scenes;

    public Act(int actNumber) {
        this.actNumber = actNumber;
        this.scenes = new ArrayList<>();
    }

    // Add a scene to the act
    public void addScene(Scene scene) {
        scenes.add(scene);
    }

    // Load acts from a text file
    public static List<Act> loadActs(Context context, String fileName, int actNumber) throws IOException {
        List<Act> acts = new ArrayList<>();
        Act act = new Act(actNumber);

        InputStream is = context.getAssets().open(fileName);

        BufferedReader reader = new BufferedReader(new InputStreamReader(is));
        String line;

        while ((line = reader.readLine()) != null) {
            String[] parts = line.split(" - ");

            int sceneNumber = Integer.parseInt(parts[0].trim());

            String title = parts[1].split(":")[0].trim();

            Scene scene = new Scene(sceneNumber, title);
            String[] roleNames = parts[1].split(":")[1].split(",");


            for (String roleName : roleNames) {
                scene.addRole(new Role(roleName.trim()));
            }
            act.addScene(scene);
        }
        reader.close();
        acts.add(act);
        return acts;
    }

    // Getters and setters
    public int getActNumber() {
        return actNumber;
    }

    public void setActNumber(int actNumber) {
        this.actNumber = actNumber;
    }

    public List<Scene> getScenes() {
        return scenes;
    }

    public void setScenes(List<Scene> scenes) {
        this.scenes = scenes;
    }
}
