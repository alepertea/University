package socialnetwork.ui;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;

public class MainFX extends Application
{
    @Override
    public void start(Stage stage) throws Exception
    {
        FXMLLoader loader= new FXMLLoader();
        loader.setLocation(getClass().getResource("/view/Login.fxml"));
        GridPane root = loader.load();
        Scene scene = new Scene(root, 493, 600);
        stage.setTitle("Login");
        stage.setScene(scene);
        stage.setResizable(false);
        stage.getIcons().add(new Image("/images/login.png"));
        stage.show();
    }

    public static void main(String[] args)
    {
        launch(args);
    }
}
