package edu.utsa.cs3443.tro893_lab5.model;

import java.util.ArrayList;
import java.util.List;

public class Scene {
    private int sceneNumber;
    private String title;
    private List<Role> roles;

    public Scene(int sceneNumber, String title) {
        this.sceneNumber = sceneNumber;
        this.title = title;
        this.roles = new ArrayList<>();
    }

    // Add a role to the scene
    public void addRole(Role role) {
        roles.add(role);
    }

    // Getters and setters
    public int getSceneNumber() {
        return sceneNumber;
    }

    public void setSceneNumber(int sceneNumber) {
        this.sceneNumber = sceneNumber;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public List<Role> getRoles() {
        return roles;
    }

    public void setRoles(List<Role> roles) {
        this.roles = roles;
    }
}

