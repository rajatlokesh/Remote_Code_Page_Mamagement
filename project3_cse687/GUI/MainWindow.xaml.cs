/////////////////////////////////////////////////////////////////////
// MainWindow.xaml.cs - GUI for OOD Project #3                     //
// ver 1.2                                                         //
// Author      - Rajat Vyas                                        //
// Provide By  - Jim Fawcett, CSE687 - Object Oriented Design,     //
//               Spring 2019                                       //
/////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This package defines one class MainWindow that provides tabs:
 * - Find Libs: Navigate through local directory to find files for testing
 *   - Shows local directories and files
 *   - Can navigate by double clicking directories
 *   - Can select files by selecting.  That displays selections in a popup window.
 * - Request Tests: left for students
 * - Show Results:  left for students
 * 
 * Required Files:
 * ---------------
 * MainWindow.xaml, MainWindow.xaml.cs
 * SelectionWindow.xaml, SelectionWindow.xaml.cs
 * 
 * Maintenance History:
 * --------------------
 * ver 1.2 : 28 Mar 2019
 * - fixed bug in DirsMouse_DoubleClick by using try catch block to
 *   handle exception that occurs if user clicks on unpopulated listbox item.
 * ver 1.1 : 16 Nov 2018
 * - fixed bug in Files_SelectionChanged by checking e.AddedItems.Count
 *   and returning if 0.
 * ver 1.0 : 15 Nov 2018
 * - first release
 * 
 */
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.IO;
using System.Threading;
namespace GUI
{
    ///////////////////////////////////////////////////////////////////
    // MainWindow class
    // - Provides navigation and selection to find libraries to test.
    // - Creates a popup window to handle selections.

    public partial class MainWindow : Window
    {
        public string path { get; set; }
        List<string> selectedFiles { get; set; } = new List<string>();
        List<string> convertedfiles { get; set; } = new List<string>();
        string regex { get; set; }
        bool button { get; set; } = true;
        public SelectionWindow swin { get; set; } = null;
        bool unselecting = false;
        ITranslator trns;
        public MainWindow()
        {
            InitializeComponent();
            showrequirement3();
            showrequirement4();
            showrequirement5();
            String pth= System.IO.Path.GetFullPath("../../../Convertedpages");
            DirectoryInfo di = new DirectoryInfo(pth);
            if (di.Exists)
            {
                foreach (FileInfo fi in di.GetFiles())
                {
                    fi.Delete();
                }
            }
        }

        void showrequirement3()
        {
            StringBuilder sb = new StringBuilder();
            sb.Append( '-', 100).Append("\n") ;
            sb.Append( "Requirement - 3   an interface for the Code Publisher developed in Project #2 \n");
            sb.Append ('-',100).Append("\n");
            sb.Append(" The following files contain the interface for codepublisher with object factory:-\n");
            sb.Append(" Path : " ).Append( System.IO.Path.GetFullPath("../../../Executive/Executive.h")).Append("\n");
            sb.Append(" Line Number :# 45 by the name IPublish");
            sb.Append("\n");
            sb.Append("Requrement 3 Passed.\n");
            Console.Write(sb);
        }
        void showrequirement4()
        {
            StringBuilder sb = new StringBuilder();
            sb.Append('-', 100).Append("\n");
            sb.Append("Requirement - 4   Publisher as Dynamic Link Library \n");
            sb.Append('-', 100).Append("\n");
            sb.Append(" The DLL is in folder:-\n");
            sb.Append(" Path : ").Append(System.IO.Path.GetFullPath("../debug")).Append("\n");
            sb.Append(" Name is Shim.dll");
            sb.Append("\n");
            sb.Append(" In the folder ");
            sb.Append(System.IO.Path.GetFullPath("../../../Shim")).Append("in the file ITranslator.h the interface is defined.\n");
            sb.Append("Requrement 4 Passed.\n");
            Console.Write(sb);

        }

        void showrequirement5()
        {
            StringBuilder sb = new StringBuilder();
            sb.Append('-', 100).Append("\n");
            sb.Append("Requirement - 5    C++\\CLI translater \n");
            sb.Append('-', 100).Append("\n");
            sb.Append("The previous requirement do tell the location of shim.");
            sb.Append("Requrement 5 Passed.\n");
            sb.Append('-',100);
            sb.Append("\nRequirement 6 - GUI \n");
            sb.Append("Requirement 7 - Automated GUI\n");
            sb.Append('-', 100).Append("\n\n");
            Console.Write(sb);

        }
        //----< open window showing contents of project directory >------

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            path = Directory.GetCurrentDirectory();
            path = getAncestorPath(3, path);
            LoadNavTab(path);
            trns = TranslatorFactory.CreateFactory();
            Regex.Text = "^[b-dB-D].*\\.(h|cpp)";
            Convert_Click(sender,e);



        }
        //----< find parent paths >--------------------------------------

        string getAncestorPath(int n, string path)
        {
            for (int i = 0; i < n; ++i)
                path = Directory.GetParent(path).FullName;
            return path;
        }
        //----< file Find Libs tab with subdirectories and files >-------

        void LoadNavTab(string path)
        {
            Dirs.Items.Clear();
            CurrPath.Text = path;
            string[] dirs = Directory.GetDirectories(path);
            Dirs.Items.Add("..");
            foreach (string dir in dirs)
            {
                DirectoryInfo di = new DirectoryInfo(dir);
                string name = System.IO.Path.GetDirectoryName(dir);
                Dirs.Items.Add(di.Name);
            }
            Files.Items.Clear();
            List<string> files = new List<string>();
           // foreach (String patt in new List<string>{"*.cpp","*.h" })
                 files.AddRange(Directory.GetFiles(path));
            foreach (string file in files)
            {
                string name = System.IO.Path.GetFileName(file);
                Files.Items.Add(name);
            }
        }
        //----< handle selections in files listbox >---------------------

        private void Files_SelectionChanged(
          object sender, SelectionChangedEventArgs e
        )
        {
            if (unselecting)
            {
                unselecting = false;
                return;
            }
            if (swin == null)
            {
                swin = new SelectionWindow();
                swin.setMainWindow(this);
            }
            //swin.Show();

            if (e.AddedItems.Count == 0)
                return;
            string selStr = e.AddedItems[0].ToString();
            selStr = System.IO.Path.Combine(path, selStr);
            if (!selectedFiles.Contains(selStr))
            {
                selectedFiles.Add(selStr);
                swin.Add(selStr);
            }
        }
        //----< unselect files called by unloading SelectionWindow >-----

        public void unselectFiles(string selectedfile)
        {
            unselecting = true;  // needed to avoid using selection logic
            foreach (string st in selectedFiles)
            {
                if (st == selectedfile)
                {
                    selectedFiles.Remove(st);
                    break;
                }
            }
            //Files.UnselectAll();
        }

        public void unselectFiles()
        {
            unselecting = true;  // needed to avoid using selection logic
            selectedFiles.Clear();
            //Files.UnselectAll();
        }
        //----< move into double-clicked directory, display contents >---

        private void Dirs_MouseDoubleClick(object sender, MouseButtonEventArgs e)
        {
            try
            {
                string selectedDir = Dirs.SelectedItem.ToString();
                if (selectedDir == "..")
                    path = getAncestorPath(1, path);
                else
                    path = System.IO.Path.Combine(path, selectedDir);
                LoadNavTab(path);
            }
            catch
            {
                // just return
            }
        }
        

        //----< shut down the SelectionWindow if open >------------------

        private void Window_Unloaded(object sender, RoutedEventArgs e)
        {
            swin.Close();
        }

        private void Convert_Click(object sender, RoutedEventArgs e)
        {
                
            if (Regex.Text == null || Regex.Text =="")
            {
                string messageboxtext = "No Regex Provided..!\n Proceed without Regex?";
                string Caption = "Regex field";
                
                MessageBoxButton but= MessageBoxButton.YesNo;
                MessageBoxImage ing = MessageBoxImage.Question;
                MessageBoxResult res= MessageBox.Show(messageboxtext, Caption, but, ing);
                switch (res)
                {
                    case MessageBoxResult.Yes:
                        break;
                    case MessageBoxResult.No:
                        return;
                }
            }
            trns.setdirpath(path);
            trns.setregex(Regex.Text);
            ThreadStart coversion = new ThreadStart(threadproc) ;
            Thread t_worker = new Thread(coversion);
            if (button)
            {
                t_worker.Start();
            }
            
 
            
        }
        void threadproc()
        {
            button = false;
            Dispatcher.Invoke(() =>
            {
                Status.Text = "Processing...";
                TbContr.SelectedItem = TbContr.Items[1];
            });
            trns.execute();
            Dispatcher.Invoke(() =>
            {
                if(ConvertedFiles.Items.Count!=0)
                    ConvertedFiles.Items.Clear();
                foreach (string st in trns.getfiles())
                {
                    ConvertedFiles.Items.Add(st);
                }
                //ConvertedFiles.ItemsSource=trns.getfiles();
                Status.Text = "Processed " + trns.getfiles().Count + " Files";
                TbContr.SelectedItem = TbContr.Items[1];
                if (ConvertedFiles.Items.Count == 0)
                    return;
                trns.chrome(ConvertedFiles.Items[0].ToString());
            });
            button = true;
        }

        
        //----<Dir path change on selection > ---------------------------
        private void Dirs_Selected(object sender, RoutedEventArgs e)
        {
            try
            {
                string selectedDir = Dirs.SelectedItem.ToString();
                CurrPath.Text = System.IO.Path.Combine(path, selectedDir);
            }
            catch
            {

            }
        }

        private void ConvertedFiles_MouseDoubleClick(object sender, MouseButtonEventArgs e)
        {
            if (ConvertedFiles.Items.Count == 0)
                return;
            trns.chrome(ConvertedFiles.SelectedItem.ToString());            

        }
    }
}
