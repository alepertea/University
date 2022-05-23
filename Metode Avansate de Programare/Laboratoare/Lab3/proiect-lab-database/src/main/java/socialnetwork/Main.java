package socialnetwork;

import socialnetwork.config.ApplicationContext;
import socialnetwork.domain.User;
import socialnetwork.domain.validators.UtilizatorValidator;
import socialnetwork.repository.Repository;
import socialnetwork.repository.database.UtilizatorDbRepository;
import socialnetwork.repository.file.UtilizatorFile;

public class Main {
    public static void main(String[] args) {
        System.out.println("ok");
       final String fileName=ApplicationContext.getPROPERTIES().getProperty("data.socialnetwork.users");
//        //String fileName="data/users.csv";
////        Repository0<Long,Utilizator> userFileRepository = new UtilizatorFile0(fileName
////                , new UtilizatorValidator());
//
        System.out.println("Reading data from file");
        Repository<Long, User> userFileRepository2 = new UtilizatorFile(fileName
                , new UtilizatorValidator());
        userFileRepository2.findAll().forEach(x-> System.out.println(x));
//
        System.out.println("Reading data from database");
        final String url = ApplicationContext.getPROPERTIES().getProperty("database.socialnetwork.url");
        final String username= ApplicationContext.getPROPERTIES().getProperty("databse.socialnetwork.username");
        final String pasword= ApplicationContext.getPROPERTIES().getProperty("database.socialnetwork.pasword");
        Repository<Long, User> userFileRepository3 =
                new UtilizatorDbRepository(url,username, pasword,  new UtilizatorValidator());

        User user = new User("Ale", "Pertea");
        user.setId(Long.parseLong("6"));
        userFileRepository3.save(user);
        userFileRepository3.findAll().forEach(System.out::println);
    }
}


