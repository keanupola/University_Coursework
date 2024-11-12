package edu.utsa.cs3443.tro893_lab5.model;

import android.content.Context;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

public class UserManager {
    private static List<User> users;

    public static void loadUsers(Context context, String fileName) throws IOException {
        if (users == null) {
            users = new ArrayList<>();
            InputStream is = context.getAssets().open(fileName);
            BufferedReader reader = new BufferedReader(new InputStreamReader(is));
            String line;

            while ((line = reader.readLine()) != null) {
                String[] parts = line.split(",");
                String username = parts[0].trim();
                String password = parts[1].trim();
                String realName = parts[2].trim();
                User user = new User(username, password, realName);
                for (int i = 3; i < parts.length; i++) {
                    if (!parts[i].isEmpty()) {
                        user.addRole(new Role(parts[i].trim()));
                    }
                }
                users.add(user);
            }
            reader.close();
        }
    }

    public static User getUserByUsername(String username) {
        if (users != null) {
            for (User user : users) {
                if (user.getUsername().equalsIgnoreCase(username)) {
                    return user;
                }
            }
        }
        return null; // User not found
    }

}
