using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.IO;

namespace test
{
    class Program
    {
        static void Main(string[] args)
        {
            string pathToProgramm;
            string pathToInputFile;
            string pathToOutputFile;
            string pathToTestFile;
            pathToProgramm = Console.ReadLine();
            pathToInputFile = Console.ReadLine();
            pathToOutputFile = Console.ReadLine();
            pathToTestFile = Console.ReadLine();
            Process proc = new Process();
            proc.StartInfo.FileName = @pathToProgramm;
            proc.StartInfo.Arguments = @pathToInputFile + " " + @pathToOutputFile;
            proc.Start();
            proc.WaitForExit();

            string[] outputFileLines = File.ReadAllLines(pathToOutputFile);
            string[] testinputFileLines = File.ReadAllLines(pathToTestFile);
            int indicator = 1;
            int buf = outputFileLines.Length < testinputFileLines.Length ? outputFileLines.Length : testinputFileLines.Length;
            for (int i = 0; i < buf; ++i) {
                    if (outputFileLines[i] != testinputFileLines[i])
                    {
                        indicator = 0;
                        Console.WriteLine("Wrong in line " + (i+1).ToString());
                    }
            }
            if (indicator == 1)
                Console.WriteLine("Correct results");
        
            Console.ReadLine();
        }
    }
}
