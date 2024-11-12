package edu.utsa.cs3443.tro893_lab5;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.ScrollView;
import android.widget.TextView;

import edu.utsa.cs3443.tro893_lab5.model.Scene;
import edu.utsa.cs3443.tro893_lab5.model.Role;
import edu.utsa.cs3443.tro893_lab5.model.Act;
import edu.utsa.cs3443.tro893_lab5.model.User;
import edu.utsa.cs3443.tro893_lab5.model.UserManager;

import java.io.IOException;
import java.util.List;

public class ActActivity extends AppCompatActivity {

    private TextView textViewActTitle;
    private ScrollView scrollViewScenes;
    private TextView textViewScenes;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_act);

        textViewActTitle = findViewById(R.id.textViewActTitle);
        scrollViewScenes = findViewById(R.id.scrollViewScenes);
        textViewScenes = findViewById(R.id.textViewScenes);

        int actNumber = getIntent().getIntExtra("act_number", 1);
        textViewActTitle.setText(String.format("Act %d", actNumber));

        String username = getIntent().getStringExtra("username");
        User user = UserManager.getUserByUsername(username);

        if (user != null) {
            try {
                List<Act> acts = Act.loadActs(this, "act" + actNumber + ".txt", actNumber);
                Act act = acts.get(0);

                // Call the method to format scenes data based on the user's roles
                String scenesText = formatScenesData(act, user);

                // Set the scenes text or "No scenes" if empty
                textViewScenes.setText(scenesText.isEmpty() ? "No scenes" : scenesText);

            } catch (IOException e) {
                e.printStackTrace();
                textViewScenes.setText("Error loading scenes.");
            }
        } else {
            textViewScenes.setText("User not found.");
        }
    }

    private String formatScenesData(Act act, User user) {
        StringBuilder formattedScenes = new StringBuilder();
        for (Scene scene : act.getScenes()) {
            if (sceneHasUser(scene, user)) {
                formattedScenes.append(scene.getSceneNumber())
                        .append(" - \"").append(scene.getTitle()).append("\": ");
                for (Role role : scene.getRoles()) {
                    formattedScenes.append(role.getName()).append(", ");
                }
                // Remove the last comma and space
                formattedScenes.setLength(formattedScenes.length() - 2);
                formattedScenes.append("\n");
            }
        }
        return formattedScenes.length() == 0 ? "No scenes" : formattedScenes.toString().trim();
    }

    private boolean sceneHasUser(Scene scene, User user) {
        for (Role sceneRole : scene.getRoles()) {
            String sceneRoleIdentifier = extractRoleIdentifier(sceneRole.getName());
            for (Role userRole : user.getRoles()) {
                String userRoleIdentifier = extractRoleIdentifier(userRole.getName());
                if (sceneRoleIdentifier.equalsIgnoreCase(userRoleIdentifier)) {
                    return true;
                }
            }
        }
        return false;
    }

    private String extractRoleIdentifier(String role) {
        int startIndex = role.indexOf('(');
        int endIndex = role.indexOf(')');
        if (startIndex != -1 && endIndex != -1 && startIndex < endIndex) {
            return role.substring(startIndex + 1, endIndex);
        }
        return role; // Return the original role if no parentheses found
    }
}