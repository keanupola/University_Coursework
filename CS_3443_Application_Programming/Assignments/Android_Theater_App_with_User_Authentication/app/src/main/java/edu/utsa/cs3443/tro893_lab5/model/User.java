package edu.utsa.cs3443.tro893_lab5.model;

import java.util.ArrayList;
import android.content.Context;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.List;


public class User {
    private String username;
    private String password;
    private String realName;
    private List<Role> roles = new ArrayList<>();

    public User(String username, String password, String realName) {
        this.username = username;
        this.password = password;
        this.realName = realName;
        this.roles = new ArrayList<>();
    }

    // Add a role to the user
    public void addRole(Role role) {
        roles.add(role);
    }

    // Validate user credentials
    public boolean validate(String username, String password) {
        return this.username.equals(username) && this.password.equals(password);
    }

    public static List<User> loadUsers(Context context, String fileName) throws IOException {
        List<User> users = new ArrayList<>();
        InputStream is = context.getAssets().open(fileName);
        BufferedReader reader = new BufferedReader(new InputStreamReader(is));
        String line;

        while ((line = reader.readLine()) != null) {
            String[] parts = line.split(",");

            String username = parts[0].trim();
            String password = parts[1].trim();
            String realName = parts[2].trim();

            User user = new User(username, password, realName);

            // Add roles to the user
            for (int i = 3; i < parts.length; i++) {
                if (!parts[i].isEmpty()) {
                    user.addRole(new Role(parts[i].trim()));
                }
            }

            users.add(user);
        }
        reader.close();
        return users;
    }

    public static User getUserByUsername(String username, List<User> users) {
        for (User user : users) {
            if (user.getUsername().equalsIgnoreCase(username)) {
                return user;
            }
        }
        return null; // Return null if the user is not found
    }

    public boolean hasRole(String roleName) {
        for (Role role : this.roles) {
            // Extract the identifier from the user's role
            String userRoleIdentifier = extractRoleIdentifier(role.getName());
            if (userRoleIdentifier.equalsIgnoreCase(roleName)) {
                return true;
            }
        }
        return false;
    }

    private String extractRoleIdentifier(String role) {
        // Extract the identifier within parentheses
        int startIndex = role.indexOf('(');
        int endIndex = role.indexOf(')');
        if (startIndex != -1 && endIndex != -1 && startIndex < endIndex) {
            return role.substring(startIndex + 1, endIndex);
        }
        return role; // Return the original role if no parentheses found
    }

    // Setters and Getters
    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getRealName() {
        return realName;
    }

    public void setRealName(String realName) {
        this.realName = realName;
    }

    public List<Role> getRoles() {
        return roles;
    }

    public void setRoles(List<Role> roles) {
        this.roles = roles;
    }
}
