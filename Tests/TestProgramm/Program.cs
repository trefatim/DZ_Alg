using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.IO;

namespace TestProgramm
{
    class Program
    {
        static void Main(string[] args)
        {
            string pathToProgramm;
            string pathToInputDirectory;
            string pathToOutputDirectory;
            string pathToTestDirectory;
            string[] setOfTests = 
            {
                "1.InputDataTest.txt",
                "2.AddTest.txt",
                "3.DeleteTest.txt",
                "4.SearchTest.txt",
                "5.MinMaxTest.txt"
            };
            string[] setOfResultTests =
            {
                "1.CorrectResultOfInputTest.txt",
                "2.CorrectResultOfAddTest.txt",
                "3.CorrectResultOfDeleteTest.txt",
                "4.CorrectResultOfSearchTest.txt",
                "5.CorrectResultMinMaxTest.txt"
            };
            string[] setOfResults =
            {
                "1.ResultOfInputTest.txt",
                "2.ResultOfAddTest.txt",
                "3.ResultOfDeleteTest.txt",
                "4.ResultOfSearchTest.txt",
                "5.ResultMinMaxTest.txt"
            };
            pathToProgramm = Console.ReadLine();
            pathToInputDirectory = Console.ReadLine();
            pathToOutputDirectory = Console.ReadLine();
            pathToTestDirectory = Console.ReadLine();
            for (int j = 0; j < setOfTests.Length; ++j)
            {
                Console.WriteLine("Test " + (j + 1).ToString() + ":");
                Process proc = new Process();
                proc.StartInfo.FileName = @pathToProgramm;
                proc.StartInfo.Arguments = @pathToInputDirectory + @"\" + setOfTests[j] + " " + @pathToOutputDirectory + @"\" + setOfResults[j];
                proc.Start();
                proc.WaitForExit();
                
                string[] outputFileLines = File.ReadAllLines(pathToOutputDirectory + @"\" + setOfResults[j]);
                string[] testinputFileLines = File.ReadAllLines(pathToTestDirectory + @"\" + setOfResultTests[j]);
                int indicator = 1;
                int buf = outputFileLines.Length < testinputFileLines.Length ? outputFileLines.Length : testinputFileLines.Length;
                for (int i = 0; i < buf; ++i)
                {
                    if (outputFileLines[i] != testinputFileLines[i])
                    {
                        string[] outputWords = outputFileLines[i].Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
                        string[] testWords = testinputFileLines[i].Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
                        int outputTime, testTime;
                        if (int.TryParse(outputWords[outputWords.Length-2], out outputTime) && int.TryParse(testWords[testWords.Length - 2], out testTime))
                        {
                            if ( !((outputTime >= (testTime - 25)) && (outputTime <= (testTime + 25))) )
                            {
                                indicator = 0;
                                Console.WriteLine("Error in line " + (i + 1).ToString() + ": a large deviation in time: " + Math.Abs(testTime - outputTime).ToString());
                            }
                        }
                        else
                        {
                            indicator = 0;
                            Console.WriteLine("Error in line " + (i + 1).ToString() + ": wrong operation processing");
                        }
                    }
                }
                if (indicator == 1)
                    Console.WriteLine("Correct results");
                Console.WriteLine("Test " + (j + 1).ToString() + " was completed.");
                Console.WriteLine();
            }
            Console.WriteLine("All tests were completed.");
            Console.ReadLine();
        }
    }
}
