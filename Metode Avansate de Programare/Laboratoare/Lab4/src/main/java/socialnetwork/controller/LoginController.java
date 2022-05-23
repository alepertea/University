package socialnetwork.controller;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Hyperlink;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;
import javafx.scene.text.Text;
import javafx.stage.Stage;

import java.io.IOException;

public class LoginController
{
    public TextField usernameField;
    public PasswordField passwordField;

    @FXML
    public void initialize()
    {
        usernameField.setText("");
        passwordField.setText("");
    }

    public void handleSubmitButtonAction(ActionEvent event)
    {
        
    }

    public void handleSignUpAction(ActionEvent actionEvent)
    {
        try
        {
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("/view/Signup.fxml"));
            GridPane root = loader.load();
            SignupController controller = loader.getController();
            Scene scene = new Scene(root, 400, 500);
            Stage stage = new Stage();
            stage.setTitle("Sign up");
            stage.setScene(scene);
            stage.show();
        }catch (IOException e)
        {
            e.printStackTrace();
        }
    }
}
