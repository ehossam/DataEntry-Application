# DataEntry-Application Explanation and System requirements

- The application uses QT C++ for the devlopment.

# DataBase::
1. The database used for the application is MySQL because it is easy to scale, flexible, highly available and the data is well structured.
2. The database utilizes 5 tables, namely 
   Admins                |
  | ImagesProperties      |
  | InProcessImages       |
  | ProcessedImages       |
  | Users 

3. The Admins and Users Tabels are for storing users and admins data.

4. The ImagesProperties Table is set by the admins to determine the directtory of input PDF images and x-y coordinates of cropped images.

5. The  ProcessedImages Table is used to store the processed Images with the data inputted from the user.

6. The InProcessImages Table is used to ensure that all active users get new images at once.

# Detailed Description of Application::
1. The application has 2 main components (The admin and the users).

2. The application starts with a sign in / registeration page where certain rules are followed as per the hiring assignment document.

3. Once the user is registered, he can sign in using the username and password.

4. If the user is a normal user, then he will click on the user sign in button, and if admin, he will click on the admin sign in.

5. After logging in, the admin can modify the path location of files to input to the application. Also, he can change the coordinates for the cropped images to be shown on the user page. The admin must click submit for the changes to take action.

6. The user page is divided into three images where each image is shown depedning on the x, y coordinates depemding on the data inputted by the admins.

7. The user can press tab or enter when done with an image to load the next until done.

8. The user can log out and see the session summary.
