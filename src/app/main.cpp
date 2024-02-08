#include "../Model/User.hpp"
#include "../Model/Room.hpp"
#include "../Model/Question.hpp"
#include "../Model/Option.hpp"
#include "../Model/Category.hpp"
#include "../Model/Answer.hpp"
#include <bits/stdc++.h>

int main () {

    /*
        getAll
        create new with increasing id and save
        getAll
        create new with default value and save
        getAll
        edit the new with default value
        getAll
        delete the new with default value
        getAll
        delete the new with increasing id
        getAll
    */

    // Scenario 1: Get all users
    std::vector<User> allUsers = User::getAll();
    std::cout << "All Users:\n";
    for (const auto &user : allUsers)
    {
        std::cout << "ID: " << user.id << ", Name: " << user.name
                  << ", Email: " << user.email << ", Password: " << user.password
                  << ", Status: " << user.status << ", Role: " << user.role << "\n";
    }

    // Scenario 2: Create new user with increasing id
    User newUserIncreasingId("New User (Increasing ID)", "newuser@example.com", "newpassword", 1, "User");
    std::cout << "\nNew User (Increasing ID) Created:\n";
    std::cout << "ID: " << newUserIncreasingId.id << ", Name: " << newUserIncreasingId.name
              << ", Email: " << newUserIncreasingId.email << ", Password: " << newUserIncreasingId.password
              << ", Status: " << newUserIncreasingId.status << ", Role: " << newUserIncreasingId.role << "\n";
    User::create(newUserIncreasingId);

    // Scenario 3: Get all users after creating new user with increasing id
    std::vector<User> allUsersAfterCreatingIncreasingId = User::getAll();
    std::cout << "\nAll Users After Creating New User (Increasing ID):\n";
    for (const auto &user : allUsersAfterCreatingIncreasingId)
    {
        std::cout << "ID: " << user.id << ", Name: " << user.name
                  << ", Email: " << user.email << ", Password: " << user.password
                  << ", Status: " << user.status << ", Role: " << user.role << "\n";
    }

    // Scenario 4: Create new user with default values
    User newUserDefaultValues("New User (Default Values)", "newuser2@example.com", "newpassword2");
    std::cout << "\nNew User (Default Values) Created:\n";
    std::cout << "ID: " << newUserDefaultValues.id << ", Name: " << newUserDefaultValues.name
              << ", Email: " << newUserDefaultValues.email << ", Password: " << newUserDefaultValues.password
              << ", Status: " << newUserDefaultValues.status << ", Role: " << newUserDefaultValues.role << "\n";
    User::create(newUserDefaultValues);

    // Scenario 5: Get all users after creating new user with default values
    std::vector<User> allUsersAfterCreatingDefaultValues = User::getAll();
    std::cout << "\nAll Users After Creating New User (Default Values):\n";
    for (const auto &user : allUsersAfterCreatingDefaultValues)
    {
        std::cout << "ID: " << user.id << ", Name: " << user.name
                  << ", Email: " << user.email << ", Password: " << user.password
                  << ", Status: " << user.status << ", Role: " << user.role << "\n";
    }

    // Scenario 6: Edit the new user with default values
    newUserDefaultValues.name = "Updated Name";
    newUserDefaultValues.email = "updatedname@example.com";
    newUserDefaultValues.password = "updatedpassword";
    newUserDefaultValues.status = 2;
    newUserDefaultValues.role = "Admin";

    User updatedUser = User::edit(newUserDefaultValues);
    std::cout << "\nUpdated User (Default Values):\n";
    std::cout << "ID: " << updatedUser.id << ", Name: " << updatedUser.name
              << ", Email: " << updatedUser.email << ", Password: " << updatedUser.password
              << ", Status: " << updatedUser.status << ", Role: " << updatedUser.role << "\n";

    // Scenario 7: Get all users after editing the user with default values
    std::vector<User> allUsersAfterEditing = User::getAll();
    std::cout << "\nAll Users After Editing User (Default Values):\n";
    for (const auto &user : allUsersAfterEditing)
    {
        std::cout << "ID: " << user.id << ", Name: " << user.name
                  << ", Email: " << user.email << ", Password: " << user.password
                  << ", Status: " << user.status << ", Role: " << user.role << "\n";
    }

    // Scenario 8: Delete the new user with default values
    User userToDelete = newUserDefaultValues;
    User::Delete(userToDelete);
    std::cout << "\nDeleted User (Default Values):\n";
    std::cout << "ID: " << userToDelete.id << ", Name: " << userToDelete.name
              << ", Email: " << userToDelete.email << ", Password: " << userToDelete.password
              << ", Status: " << userToDelete.status << ", Role: " << userToDelete.role << "\n";

    // Scenario 9: Get all users after deleting the user with default values
    std::vector<User> allUsersAfterDeleting = User::getAll();
    std::cout << "\nAll Users After Deleting User (Default Values):\n";
    for (const auto &user : allUsersAfterDeleting)
    {
        std::cout << "ID: " << user.id << ", Name: " << user.name
                  << ", Email: " << user.email << ", Password: " << user.password
                  << ", Status: " << user.status << ", Role: " << user.role << "\n";
    }

    // Scenario 10: Delete the new user with increasing id
    User::Delete(newUserIncreasingId);
    std::cout << "\nDeleted User (Increasing ID):\n";
    std::cout << "ID: " << newUserIncreasingId.id << ", Name: " << newUserIncreasingId.name
              << ", Email: " << newUserIncreasingId.email << ", Password: " << newUserIncreasingId.password
              << ", Status: " << newUserIncreasingId.status << ", Role: " << newUserIncreasingId.role << "\n";

    // Scenario 11: Get all users after deleting the user with increasing id
    std::vector<User> allUsersAfterDeletingIncreasingId = User::getAll();
    std::cout << "\nAll Users After Deleting User (Increasing ID):\n";
    for (const auto &user : allUsersAfterDeletingIncreasingId)
    {
        std::cout << "ID: " << user.id << ", Name: " << user.name
                  << ", Email: " << user.email << ", Password: " << user.password
                  << ", Status: " << user.status << ", Role: " << user.role << "\n";
    }

    /*
        getAll
        create new with increasing id and save
        getAll
        edit the new with increasing id
        getAll
        delete the new with increasing id
        getAll
    */

    // Scenario 1: Get all rooms
    std::vector<Room> allRooms = Room::getAll();
    std::cout << "All Rooms:\n";
    for (const auto &room : allRooms)
    {
        std::cout << "ID: " << room.id << ", Name: " << room.name
                  << ", Capacity: " << room.capacity << ", Type: " << room.type
                  << ", Start Time: " << room.start_time << ", Close Time: " << room.close_time
                  << ", Status: " << room.status << ", Time Limit: " << room.time_limit << "\n";
    }

    // Scenario 2: Create new room with increasing id
    Room newRoomIncreasingId("New Room", 10, "Conference", "09:00", "18:00", 1, 60); // Replace with appropriate values
    std::cout << "\nNew Room (Increasing ID):\n";
    std::cout << "ID: " << newRoomIncreasingId.id << ", Name: " << newRoomIncreasingId.name
              << ", Capacity: " << newRoomIncreasingId.capacity << ", Type: " << newRoomIncreasingId.type
              << ", Start Time: " << newRoomIncreasingId.start_time << ", Close Time: " << newRoomIncreasingId.close_time
              << ", Status: " << newRoomIncreasingId.status << ", Time Limit: " << newRoomIncreasingId.time_limit << "\n";

    // Save the new room
    Room::create(newRoomIncreasingId);

    // Scenario 3: Get all rooms after creating new room with increasing id
    std::vector<Room> allRoomsAfterCreatingIncreasingId = Room::getAll();
    std::cout << "\nAll Rooms After Creating New Room (Increasing ID):\n";
    for (const auto &room : allRoomsAfterCreatingIncreasingId)
    {
        std::cout << "ID: " << room.id << ", Name: " << room.name
                  << ", Capacity: " << room.capacity << ", Type: " << room.type
                  << ", Start Time: " << room.start_time << ", Close Time: " << room.close_time
                  << ", Status: " << room.status << ", Time Limit: " << room.time_limit << "\n";
    }

    // Scenario 4: Edit the new room with increasing id
    newRoomIncreasingId.name = "Updated Room";
    newRoomIncreasingId.capacity = 15;
    newRoomIncreasingId.type = "Meeting";
    newRoomIncreasingId.start_time = "10:00";
    newRoomIncreasingId.close_time = "17:00";
    newRoomIncreasingId.status = 0;
    newRoomIncreasingId.time_limit = 30;

    Room updatedRoom = Room::edit(newRoomIncreasingId);
    std::cout << "\nUpdated Room (Increasing ID):\n";
    std::cout << "ID: " << updatedRoom.id << ", Name: " << updatedRoom.name
              << ", Capacity: " << updatedRoom.capacity << ", Type: " << updatedRoom.type
              << ", Start Time: " << updatedRoom.start_time << ", Close Time: " << updatedRoom.close_time
              << ", Status: " << updatedRoom.status << ", Time Limit: " << updatedRoom.time_limit << "\n";

    // Scenario 5: Get all rooms after editing the room with increasing id
    std::vector<Room> allRoomsAfterEditing = Room::getAll();
    std::cout << "\nAll Rooms After Editing Room (Increasing ID):\n";
    for (const auto &room : allRoomsAfterEditing)
    {
        std::cout << "ID: " << room.id << ", Name: " << room.name
                  << ", Capacity: " << room.capacity << ", Type: " << room.type
                  << ", Start Time: " << room.start_time << ", Close Time: " << room.close_time
                  << ", Status: " << room.status << ", Time Limit: " << room.time_limit << "\n";
    }

    // Scenario 6: Delete the new room with increasing id
    Room roomToDelete = newRoomIncreasingId;
    Room::Delete(roomToDelete);
    std::cout << "\nDeleted Room (Increasing ID):\n";
    std::cout << "ID: " << roomToDelete.id << ", Name: " << roomToDelete.name
              << ", Capacity: " << roomToDelete.capacity << ", Type: " << roomToDelete.type
              << ", Start Time: " << roomToDelete.start_time << ", Close Time: " << roomToDelete.close_time
              << ", Status: " << roomToDelete.status << ", Time Limit: " << roomToDelete.time_limit << "\n";

    // Scenario 7: Get all rooms after deleting the room with increasing id
    std::vector<Room> allRoomsAfterDeletingIncreasingId = Room::getAll();
    std::cout << "\nAll Rooms After Deleting Room (Increasing ID):\n";
    for (const auto &room : allRoomsAfterDeletingIncreasingId)
    {
        std::cout << "ID: " << room.id << ", Name: " << room.name
                  << ", Capacity: " << room.capacity << ", Type: " << room.type
                  << ", Start Time: " << room.start_time << ", Close Time: " << room.close_time
                  << ", Status: " << room.status << ", Time Limit: " << room.time_limit << "\n";
    }

    /*
        getAll
        create new with increasing id and save
        getAll
        edit the new with increasing id
        getAll
        delete the new with increasing id
        getAll
    */

    // Scenario 1: Get all questions
    std::vector<Question> allQuestions = Question::getAll();
    std::cout << "All Questions:\n";
    for (const auto &question : allQuestions)
    {
        std::cout << "ID: " << question.id << ", Title: " << question.title << ", Level: " << question.level << ", Category ID: " << question.category_id << "\n";
    }

    // Scenario 2: Create a new question with increasing id and save
    Question newQuestion("New Question", 1, 1);
    newQuestion = Question::create(newQuestion);
    std::cout << "\nNew Question Created:\n";
    std::cout << "ID: " << newQuestion.id << ", Title: " << newQuestion.title << ", Level: " << newQuestion.level << ", Category ID: " << newQuestion.category_id << "\n";

    // Scenario 3: Get all questions after creation
    allQuestions = Question::getAll();
    std::cout << "\nAll Questions after Creation:\n";
    for (const auto &question : allQuestions)
    {
        std::cout << "ID: " << question.id << ", Title: " << question.title << ", Level: " << question.level << ", Category ID: " << question.category_id << "\n";
    }

    // Scenario 4: Edit the new question with increasing id
    newQuestion.title = "Updated Question";
    newQuestion.level = 2;
    newQuestion.category_id = 2;
    Question::edit(newQuestion);
    std::cout << "\nUpdated Question:\n";
    std::cout << "ID: " << newQuestion.id << ", Title: " << newQuestion.title << ", Level: " << newQuestion.level << ", Category ID: " << newQuestion.category_id << "\n";

    // Scenario 5: Get all questions after update
    allQuestions = Question::getAll();
    std::cout << "\nAll Questions after Update:\n";
    for (const auto &question : allQuestions)
    {
        std::cout << "ID: " << question.id << ", Title: " << question.title << ", Level: " << question.level << ", Category ID: " << question.category_id << "\n";
    }

    // Scenario 6: Delete the new question with increasing id
    Question::Delete(newQuestion);
    std::cout << "\nDeleted Question:\n";
    std::cout << "ID: " << newQuestion.id << ", Title: " << newQuestion.title << ", Level: " << newQuestion.level << ", Category ID: " << newQuestion.category_id << "\n";

    // Scenario 7: Get all questions after deletion
    allQuestions = Question::getAll();
    std::cout << "\nAll Questions after Deletion:\n";
    for (const auto &question : allQuestions)
    {
        std::cout << "ID: " << question.id << ", Title: " << question.title << ", Level: " << question.level << ", Category ID: " << question.category_id << "\n";
    }

    /*
        getAll
        create new with increasing id and save
        getAll
        create new with default value and save
        getAll
        edit the new with default value
        getAll
        delete the new with default value
        getAll
        delete the new with increasing id
        getAll
    */

    // Scenario 1: Get all options
    std::vector<Option> allOptions = Option::getAll();
    std::cout << "All Options:\n";
    for (const auto &option : allOptions)
    {
        std::cout << "ID: " << option.id << ", Question ID: " << option.question_id
                  << ", Content: " << option.content << ", Is Right: " << option.is_right << "\n";
    }

    // Scenario 2: Create a new option with increasing id and save
    Option newOption(1, "New Option 1", true);
    newOption = Option::create(newOption);
    std::cout << "\nNew Option Created:\n";
    std::cout << "ID: " << newOption.id << ", Question ID: " << newOption.question_id
              << ", Content: " << newOption.content << ", Is Right: " << newOption.is_right << "\n";

    // Scenario 3: Create a new option with default value and save
    Option newDefaultOption(1, "New Option 2");
    newDefaultOption = Option::create(newDefaultOption);
    std::cout << "\nNew Default Option Created:\n";
    std::cout << "ID: " << newDefaultOption.id << ", Question ID: " << newDefaultOption.question_id
              << ", Content: " << newDefaultOption.content << ", Is Right: " << newDefaultOption.is_right << "\n";

    // Scenario 4: Get all options after creation
    allOptions = Option::getAll();
    std::cout << "\nAll Options after Creation:\n";
    for (const auto &option : allOptions)
    {
        std::cout << "ID: " << option.id << ", Question ID: " << option.question_id
                  << ", Content: " << option.content << ", Is Right: " << option.is_right << "\n";
    }

    // Scenario 5: Edit the new option with default value
    newDefaultOption.content = "Updated Option";
    newDefaultOption.is_right = true;
    Option::edit(newDefaultOption);
    std::cout << "\nUpdated Option:\n";
    std::cout << "ID: " << newDefaultOption.id << ", Question ID: " << newDefaultOption.question_id
              << ", Content: " << newDefaultOption.content << ", Is Right: " << newDefaultOption.is_right << "\n";

    // Scenario 6: Get all options after update
    allOptions = Option::getAll();
    std::cout << "\nAll Options after Update:\n";
    for (const auto &option : allOptions)
    {
        std::cout << "ID: " << option.id << ", Question ID: " << option.question_id
                  << ", Content: " << option.content << ", Is Right: " << option.is_right << "\n";
    }

    // Scenario 7: Delete the new option with default value
    Option::Delete(newDefaultOption);
    std::cout << "\nDeleted Option:\n";
    std::cout << "ID: " << newDefaultOption.id << ", Question ID: " << newDefaultOption.question_id
              << ", Content: " << newDefaultOption.content << ", Is Right: " << newDefaultOption.is_right << "\n";

    // Scenario 8: Delete the new option with increasing id
    Option::Delete(newOption);
    std::cout << "\nDeleted Option:\n";
    std::cout << "ID: " << newOption.id << ", Question ID: " << newOption.question_id
              << ", Content: " << newOption.content << ", Is Right: " << newOption.is_right << "\n";

    // Scenario 9: Get all options after deletion
    allOptions = Option::getAll();
    std::cout << "\nAll Options after Deletion:\n";
    for (const auto &option : allOptions)
    {
        std::cout << "ID: " << option.id << ", Question ID: " << option.question_id
                  << ", Content: " << option.content << ", Is Right: " << option.is_right << "\n";
    }

    /*
        getAll
        create new with increasing id and save
        getAll
        edit the new with increasing id
        getAll
        delete the new with increasing id
        getAll
    */

    // Scenario 1: Get all categories
    std::vector<Category> allCategories = Category::getAll();
    std::cout << "All Categories:\n";
    for (const auto &category : allCategories)
    {
        std::cout << "ID: " << category.id << ", Name: " << category.name << ", Slug: " << category.slug << "\n";
    }

    // Scenario 2: Create a new category with increasing id and save
    Category newCategory("New Category", "new-category");
    newCategory = Category::create(newCategory);
    std::cout << "\nNew Category Created:\n";
    std::cout << "ID: " << newCategory.id << ", Name: " << newCategory.name << ", Slug: " << newCategory.slug << "\n";

    // Scenario 3: Get all categories after creation
    allCategories = Category::getAll();
    std::cout << "\nAll Categories after Creation:\n";
    for (const auto &category : allCategories)
    {
        std::cout << "ID: " << category.id << ", Name: " << category.name << ", Slug: " << category.slug << "\n";
    }

    // Scenario 4: Edit the new category with increasing id
    newCategory.name = "Updated Category";
    newCategory.slug = "updated-category";
    Category::edit(newCategory);
    std::cout << "\nUpdated Category:\n";
    std::cout << "ID: " << newCategory.id << ", Name: " << newCategory.name << ", Slug: " << newCategory.slug << "\n";

    // Scenario 5: Get all categories after update
    allCategories = Category::getAll();
    std::cout << "\nAll Categories after Update:\n";
    for (const auto &category : allCategories)
    {
        std::cout << "ID: " << category.id << ", Name: " << category.name << ", Slug: " << category.slug << "\n";
    }

    // Scenario 6: Delete the new category with increasing id
    Category::Delete(newCategory);
    std::cout << "\nDeleted Category:\n";
    std::cout << "ID: " << newCategory.id << ", Name: " << newCategory.name << ", Slug: " << newCategory.slug << "\n";

    // Scenario 7: Get all categories after deletion
    allCategories = Category::getAll();
    std::cout << "\nAll Categories after Deletion:\n";
    for (const auto &category : allCategories)
    {
        std::cout << "ID: " << category.id << ", Name: " << category.name << ", Slug: " << category.slug << "\n";
    }

    /*
        getAll
        create new with increasing id and save
        getAll
        create new with default value and save
        getAll
        edit the new with default value
        getAll
        delete the new with default value
        getAll
        delete the new with increasing id
        getAll
    */

    // Scenario 1: Get all answers
    std::vector<Answer> allAnswers = Answer::getAll();
    std::cout << "All Answers:\n";
    for (const auto &answer : allAnswers)
    {
        std::cout << "ID: " << answer.id << ", User ID: " << answer.user_id
                  << ", Room ID: " << answer.room_id << ", Option ID: " << answer.option_id
                  << ", Result: " << answer.result << "\n";
    }

    // Scenario 2: Create new answer with increasing id
    Answer newAnswerIncreasingId(1, 1, 1, 1); // Replace with appropriate values
    std::cout << "\nNew Answer (Increasing ID):\n";
    std::cout << "ID: " << newAnswerIncreasingId.id << ", User ID: " << newAnswerIncreasingId.user_id
              << ", Room ID: " << newAnswerIncreasingId.room_id << ", Option ID: " << newAnswerIncreasingId.option_id
              << ", Result: " << newAnswerIncreasingId.result << "\n";

    // Save the new answer
    Answer::create(newAnswerIncreasingId);

    // Scenario 3: Get all answers after creating new answer with increasing id
    std::vector<Answer> allAnswersAfterCreatingIncreasingId = Answer::getAll();
    std::cout << "\nAll Answers After Creating New Answer (Increasing ID):\n";
    for (const auto &answer : allAnswersAfterCreatingIncreasingId)
    {
        std::cout << "ID: " << answer.id << ", User ID: " << answer.user_id
                  << ", Room ID: " << answer.room_id << ", Option ID: " << answer.option_id
                  << ", Result: " << answer.result << "\n";
    }

    // Scenario 4: Create new answer with default values
    Answer newAnswerDefaultValues(1, 1); // Replace with appropriate values
    std::cout << "\nNew Answer (Default Values):\n";
    std::cout << "ID: " << newAnswerDefaultValues.id << ", User ID: " << newAnswerDefaultValues.user_id
              << ", Room ID: " << newAnswerDefaultValues.room_id << ", Option ID: " << newAnswerDefaultValues.option_id
              << ", Result: " << newAnswerDefaultValues.result << "\n";

    // Save the new answer
    Answer::create(newAnswerDefaultValues);

    // Scenario 5: Get all answers after creating new answer with default values
    std::vector<Answer> allAnswersAfterCreatingDefaultValues = Answer::getAll();
    std::cout << "\nAll Answers After Creating New Answer (Default Values):\n";
    for (const auto &answer : allAnswersAfterCreatingDefaultValues)
    {
        std::cout << "ID: " << answer.id << ", User ID: " << answer.user_id
                  << ", Room ID: " << answer.room_id << ", Option ID: " << answer.option_id
                  << ", Result: " << answer.result << "\n";
    }

    // Scenario 6: Edit the new answer with default values
    newAnswerDefaultValues.user_id = 2; // Replace with appropriate values
    newAnswerDefaultValues.room_id = 2;
    newAnswerDefaultValues.option_id = 2;
    newAnswerDefaultValues.result = 2;

    Answer updatedAnswer = Answer::edit(newAnswerDefaultValues);
    std::cout << "\nUpdated Answer (Default Values):\n";
    std::cout << "ID: " << updatedAnswer.id << ", User ID: " << updatedAnswer.user_id
              << ", Room ID: " << updatedAnswer.room_id << ", Option ID: " << updatedAnswer.option_id
              << ", Result: " << updatedAnswer.result << "\n";

    // Scenario 7: Get all answers after editing the answer with default values
    std::vector<Answer> allAnswersAfterEditing = Answer::getAll();
    std::cout << "\nAll Answers After Editing Answer (Default Values):\n";
    for (const auto &answer : allAnswersAfterEditing)
    {
        std::cout << "ID: " << answer.id << ", User ID: " << answer.user_id
                  << ", Room ID: " << answer.room_id << ", Option ID: " << answer.option_id
                  << ", Result: " << answer.result << "\n";
    }

    // Scenario 8: Delete the new answer with default values
    Answer answerToDelete = newAnswerDefaultValues;
    Answer::Delete(answerToDelete);
    std::cout << "\nDeleted Answer (Default Values):\n";
    std::cout << "ID: " << answerToDelete.id << ", User ID: " << answerToDelete.user_id
              << ", Room ID: " << answerToDelete.room_id << ", Option ID: " << answerToDelete.option_id
              << ", Result: " << answerToDelete.result << "\n";

    // Scenario 9: Get all answers after deleting the answer with default values
    std::vector<Answer> allAnswersAfterDeleting = Answer::getAll();
    std::cout << "\nAll Answers After Deleting Answer (Default Values):\n";
    for (const auto &answer : allAnswersAfterDeleting)
    {
        std::cout << "ID: " << answer.id << ", User ID: " << answer.user_id
                  << ", Room ID: " << answer.room_id << ", Option ID: " << answer.option_id
                  << ", Result: " << answer.result << "\n";
    }

    // Scenario 10: Delete the new answer with increasing id
    Answer::Delete(newAnswerIncreasingId);
    std::cout << "\nDeleted Answer (Increasing ID):\n";
    std::cout << "ID: " << newAnswerIncreasingId.id << ", User ID: " << newAnswerIncreasingId.user_id
              << ", Room ID: " << newAnswerIncreasingId.room_id << ", Option ID: " << newAnswerIncreasingId.option_id
              << ", Result: " << newAnswerIncreasingId.result << "\n";

    // Scenario 11: Get all answers after deleting the answer with increasing id
    std::vector<Answer> allAnswersAfterDeletingIncreasingId = Answer::getAll();
    std::cout << "\nAll Answers After Deleting Answer (Increasing ID):\n";
    for (const auto &answer : allAnswersAfterDeletingIncreasingId)
    {
        std::cout << "ID: " << answer.id << ", User ID: " << answer.user_id
                  << ", Room ID: " << answer.room_id << ", Option ID: " << answer.option_id
                  << ", Result: " << answer.result << "\n";
    }
    return 0;
}