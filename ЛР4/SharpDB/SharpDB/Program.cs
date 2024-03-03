using System;
using Microsoft.Data.Sqlite;

namespace Stoler_lr4
{
    class Program
    {
        static void Main(string[] args)
        {
            // Устанавливаем соединение с базой данных SQLite
            using (var db = new SqliteConnection("Data Source=db.sqlite"))
            {
                db.Open(); // Открываем соединение с базой данных
                var dbc = db.CreateCommand();// Создаем объект для выполнения SQL-запросов


                while (true)
                {

                    Console.WriteLine("Меню:");
                    Console.WriteLine("1. Вывести все данные");
                    Console.WriteLine("2. Показать -- незащищенное чтение(unsafe)");
                    Console.WriteLine("3. Показать -- защищенное чтение(safe)");
                    Console.WriteLine("4. Генерация БД");
                    Console.WriteLine("5. Выход");
                    Console.WriteLine("");
                    Console.WriteLine("Введите выбранную Вами цифру:");

                    int a = int.Parse(Console.ReadLine());

                    switch (a)
                    {
                        case 1:
                            {

                                dbc.CommandText = "SELECT name FROM test";
                                dbc.ExecuteNonQuery();
                                SqliteDataReader reader = dbc.ExecuteReader(); //Для чтения данных из базы данных SQLite применяется метод 
                                while (reader.Read())
                                    Console.WriteLine("{0}", reader.GetString(0));
                                reader.Close();
                                break;
                            }
                        //SQL-запрос для выбора возраста объекта по введенному имени.
                        //Метод подвержен SQL-инъекциям, так как пользовательский ввод вставляется напрямую в запрос.
                        case 2:
                            {
                                Console.WriteLine("\nВведите имя объекта:");
                                string b = Console.ReadLine();

                                // Выполняем незащищенное чтение: вставляем имя пользователя напрямую в SQL-запрос
                                //dbc.CommandText = $"SELECT age FROM test WHERE name  = '{b}'";
                                dbc.CommandText = $"DELETE FROM test WHERE name = '{b}'";
                                dbc.ExecuteNonQuery();

                                SqliteDataReader reader = dbc.ExecuteReader();
                                while (reader.Read())
                                    Console.WriteLine("{0}", reader.GetString(0));
                                reader.Close();
                                break;
                            }
                        //В этом методе используется подготовленный запрос для безопасного выбора возраста объекта по имени.
                        case 3:
                            {
                                Console.WriteLine("\nВведите имя объекта:");
                                string b = Console.ReadLine();

                                // Выполняем защищенное чтение: используем подготовленный запрос
                                using (SqliteCommand command = new SqliteCommand("delete from test where name like @object", db))
                                {
                                    command.Parameters.AddWithValue("@object", b);
                                    var output = command.ExecuteScalar();
                                    if (output == null)
                                        Console.WriteLine("Такого объекта нет");
                                    else
                                        Console.WriteLine(output);
                                }
                                break;
                            }
                        case 4:
                            {
                                // Удаляем таблицу "test", если она существует
                                dbc.CommandText = $"DROP TABLE IF EXISTS test";
                                dbc.ExecuteNonQuery();

                                // Создаем таблицу "test", если она не существует
                                dbc.CommandText = @" CREATE TABLE IF NOT EXISTS test(
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    name TEXT,
                    age INTEGER)";
                                dbc.ExecuteNonQuery();

                                dbc.CommandText = $"INSERT INTO test VALUES (NULL, 'Иван', {19})";
                                dbc.ExecuteNonQuery();
                                dbc.CommandText = $"INSERT INTO test VALUES (NULL, 'Илья', {21})";
                                dbc.ExecuteNonQuery();
                                dbc.CommandText = $"INSERT INTO test VALUES (NULL, 'Екатерина', {15})";
                                dbc.ExecuteNonQuery();
                                dbc.CommandText = $"INSERT INTO test VALUES (NULL, 'Михаил', {22})";
                                dbc.ExecuteNonQuery();
                                dbc.CommandText = $"INSERT INTO test VALUES (NULL, 'Алексей', {23})";
                                dbc.ExecuteNonQuery();


                                break;
                            }
                        default:
                            { return; }
                    }
                }
            }
        }
    }
}
