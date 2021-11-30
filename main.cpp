#include <iostream>
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::fixed;
using std::ios;
using std::left;
using std::right;
using std::showpoint;

#include <fstream>
using std::ofstream;
using std::ostream;
using std::fstream;

#include <iomanip>
using std::setw;
using std::setprecision;

#include <cstdlib> 
using std::exit; // exit function prototype

#include "Product.h" // ClientData class definition
/*
using namespace std;
*/
int enterChoice();
void createTextFile( fstream& );
void addRecord( fstream& );
void updateRecord( fstream& );
void newRecord( fstream& );
void deleteRecord( fstream& );
void displayRecord(fstream&);
void outputLine( ostream&, const Product & );
void calculateTotal( fstream& );
int getPartNumber( const char * const );


enum Choices { CREATE = 1, DISPLAY,ENTER,DELETE,UPDATE,CALCULATE, END };

int main()
{
	 
   fstream inOutPart;
   
   int choice;

   while ( ( choice = enterChoice() ) != END ) 
   {
      switch ( choice ) 
      {
         case CREATE:
            createTextFile( inOutPart );
            break;
		 case DISPLAY: //display the content of file
		    displayRecord(inOutPart);
			break;
         case ENTER:
            addRecord( inOutPart );
            break;
		 case UPDATE:
			updateRecord( inOutPart );
			break;
		 case DELETE:
			deleteRecord( inOutPart );
			break;
		 case CALCULATE:
			calculateTotal( inOutPart );
			break;
         default: // display error if user does not select valid choice
            cerr << "Incorrect choice" << endl;
            break;
      } // end switch

      inOutPart.clear(); // reset end-of-file indicator
   } // end while

   inOutPart.close();

   return 0;

}

void calculateTotal(fstream& ENTERFile)
{
	double costTotal = 0.0;
	int totalQuan = 0;
	int totalRecords = 0;

	ENTERFile.seekg(0);
	Product prod;

	ENTERFile.read( reinterpret_cast< char * >( &prod ), sizeof( Product ) );

	while ( ENTERFile && !ENTERFile.eof() ) 
	{

		if ( prod.getPartNumber()!= 0 )
		{
			totalRecords++;
			costTotal+=prod.getCost()*prod.getQuantity();
			totalQuan+=prod.getQuantity();
		}


		   ENTERFile.read( reinterpret_cast< char * >( &prod ), sizeof( Product ) );
	}
	ENTERFile.clear();

	cout<<"Total # of Records: "<<totalRecords<<endl;
	cout<<"Total Quantity: "<<totalQuan<<endl;
	cout<<"Total Inventory Cost: "<<setprecision(2)<<costTotal<<endl<<endl;

}

int enterChoice()
{
	// display available options
	for (int stars=0; stars<39; stars++)
		cout <<"*";
   cout << "\nEnter 1 for opening data file" << endl
      << "Enter 2 for listing all the records" << endl
     // << "3 - add a new part" << endl
     // << "4 - delete a part" << endl
	  << "Enter 3 for entering a new record"<<endl
	  << "Enter 4 for deleting a record"<<endl
	  << "Enter 5 for updating a record"<<endl
	  << "Enter 6 for calculating the total inventory cost"<<endl
      << "Enter 7 to exit\n";
   	for (int stars=0; stars<39; stars++)
		cout <<"*";

	int menuChoice;

	//do
	//{
		cout << "\nChoice: ";
		cin >> menuChoice; // input menu selection from user
	//} while ((menuChoice!=1)||(menuChoice!=2)||(menuChoice!=3)||(menuChoice!=4));

   return menuChoice;

}


void createTextFile( fstream& PartFile )
{

   Product prod; 
   char nameFile[50];
   if (PartFile.is_open())
	   PartFile.close();
   cout << "\nEnter the file name: ";
   cin >> nameFile;
   ofstream newfile;
   //fstream PartFile;
   PartFile.open(nameFile, ios::out|ios::in|ios::binary);
   
		
   if ( !PartFile.is_open()) 
   {
		cerr << "File does not exist. create the data file.\n" << endl;
		newfile.open(nameFile, ios::out|ios::binary);
	    if(!newfile)
		{
			cout<<"could not open file"<<nameFile<<endl;
		}


   
  
	   //PartFile.open(nameFile, ios::app|ios::out|ios::in|ios::binary);
   
	   for ( int i = 0; i < 100; i++ )
       {
		   //prod.setPartNumber(i);
		   newfile.write( reinterpret_cast< const char * >( &prod ),sizeof( Product ) );
       }

	   newfile.close();
	   PartFile.open(nameFile, ios::out|ios::in|ios::binary);

   }
   else
	   cout << "file open success.\n\n";

   //cout <<endl<<"*"<<nameFile<<" opened successfully*\n\n";

   ofstream outPrintFile( "print.txt", ios::out );
   // exit program if ofstream cannot create file
   if ( !outPrintFile ) 
   {
  
      cerr << "*File could not be created*" << endl;
      exit( 1 );
   } // end if


   outPrintFile << left << setw( 10 ) << "Part#" << setw( 16 )
      << "Part Name" << setw( 11 ) << "Quantity" << right
      << setw( 10 ) << "Price" << endl;

   // set file-position pointer to beginning 
   PartFile.clear(); //important line - program was hanging without this.
   PartFile.seekg( 0 );

   // read first record from record file
   Product proddata;
   PartFile.read( reinterpret_cast< char * >( &proddata ),
      sizeof( Product ) );

   // copy all records from record file into text file
   while ( !PartFile.eof() ) 
   {
      // write single record to text file
      if ( proddata.getPartNumber() != 0 ) // skip empty records
         outputLine( outPrintFile, proddata );

      // read next record from record file
      PartFile.read( reinterpret_cast< char * >( &proddata ), 
         sizeof( Product ) );

		 
   } // end while
   //readPartFile.close();
   //readPartFile = PartFile;
   //cout <<endl<<nameFile<<" created 100 records successfully.\n\n";

   
}














void updateRecord( fstream& ENTERFile)
{
	int partNumber;
	do
	{

	ENTERFile.seekg(0); //move to first record
	// obtain number of part number to ENTER
	partNumber = getPartNumber( "Enter the part number" );

	if (partNumber==0)
		break;

   // move file-position pointer to correct record in file
   ENTERFile.seekg( ( partNumber - 1 ) * sizeof( Product ) );

   // read first record from file
   Product prod;
   ENTERFile.read( reinterpret_cast< char * >( &prod ), 
      sizeof( Product ) );

   // ENTER record
   //if ( prod.getPartNumber() != 0 ) 
   //{
     // outputLine( cout, prod ); // display the record

	  prod.setPartNumber(partNumber);
	  string compstr = prod.getToolName();

	  //request user to enter part name
	 /*
		cout << "Enter the new tool name: ";
		string pnm;
		cin>>pnm;
		prod.setToolName(pnm);
*/
      // request user to enter cost
	  cout << "Enter the new quantity and new price: ";
      int qty;
	  double oldcost; 
      cin >>qty>>oldcost;
	  //double cost = prod.getCost();
	  prod.setCost(oldcost);

	  //cout << "\nEnter quantity/new quantity of product:";
      //int qty; 
      //cin >> qty;
      // ENTER record balance
      //int oldqty = prod.getQuantity();

      prod.setQuantity(qty );
      //outputLine( cout, prod ); // display the record

      // move file-position pointer to correct record in file
      ENTERFile.seekp( ( partNumber - 1 ) * sizeof(Product ) );

      // write ENTERd record over old record in file
      ENTERFile.write( reinterpret_cast< const char * >( &prod ), 
         sizeof( Product ) );

	  ENTERFile.clear();
   //} // end if
	  /**
   else // display error if account does not exist
      cerr << "partNumber #" << partNumber 
         << " has no information." << endl;
		 **/
	} while (partNumber!=0);
	cout << endl;
}


















void addRecord( fstream& ENTERFile)
{
	int partNumber;
	do
	{

	ENTERFile.seekg(0); //move to first record
	// obtain number of part number to ENTER
	partNumber = getPartNumber( "Enter the part number" );

	if (partNumber==0)
		break;

   // move file-position pointer to correct record in file
   ENTERFile.seekg( ( partNumber - 1 ) * sizeof( Product ) );

   // read first record from file
   Product prod;
   ENTERFile.read( reinterpret_cast< char * >( &prod ), 
      sizeof( Product ) );

   // ENTER record
   //if ( prod.getPartNumber() != 0 ) 
   //{
     // outputLine( cout, prod ); // display the record

	  prod.setPartNumber(partNumber);
	  string compstr = prod.getToolName();

	  //request user to enter part name
	  if (compstr=="")
	  {
		cout << "Enter the tool name: ";
		string pnm;
		cin>>pnm;
		prod.setToolName(pnm);
	  }

      // request user to enter cost
	  cout << "Enter quantity and price: ";
      int qty;
	  double oldcost; 
      cin >>qty>>oldcost;
	  //double cost = prod.getCost();
	  prod.setCost(oldcost);

	  //cout << "\nEnter quantity/new quantity of product:";
      //int qty; 
      //cin >> qty;
      // ENTER record balance
      //int oldqty = prod.getQuantity();

      prod.setQuantity(qty );
      //outputLine( cout, prod ); // display the record

      // move file-position pointer to correct record in file
      ENTERFile.seekp( ( partNumber - 1 ) * sizeof(Product ) );

      // write ENTERd record over old record in file
      ENTERFile.write( reinterpret_cast< const char * >( &prod ), 
         sizeof( Product ) );

	  ENTERFile.clear();
   //} // end if
	  /**
   else // display error if account does not exist
      cerr << "partNumber #" << partNumber 
         << " has no information." << endl;
		 **/
	} while (partNumber!=0);
	cout << endl;
}
void newRecord( fstream& insertFile)
{

	insertFile.seekg(0); //move to first record
	// obtain number of part to create
	int partNumber = getPartNumber( "Enter new part number:" );

   // move file-position pointer to correct record in file
   insertFile.seekg( ( partNumber - 1 ) * sizeof(Product ) );

   // read record from file
   Product prod;
   insertFile.read( reinterpret_cast< char * >( &prod ), 
      sizeof(Product) );

   // create record, if record does not previously exist
   if ( prod.getPartNumber() == 0 ) 
   {
      string name;
      int qty;
      double cost;

      // user enters part name, quantity and cost
	  cout << "Enter partname, quantity, cost:\n? ";
      cin >> setw( 15 ) >> name;
      cin >> setw( 10 ) >> qty;
      cin >> cost;

      // use values to populate account values
	  prod.setToolName(name);
	  prod.setPartNumber(partNumber);
	  prod.setQuantity(qty);
	  prod.setCost(cost);


      // move file-position pointer to correct record in file
      insertFile.seekp( ( partNumber - 1 ) * sizeof( Product ) );

      // insert record in file                       
      insertFile.write( reinterpret_cast< const char * >( &prod ),
         sizeof(Product ) );                     
   } // end if
   else // display error if account already exists
      cerr << "part number #" << partNumber
         << " already contains information." << endl;
}
void deleteRecord( fstream& deleteFile)
{
	deleteFile.seekg(0);//move to first record.
	// obtain number of part to delete
	int partNumber = getPartNumber( "Enter part number to delete:" );

   // move file-position pointer to correct record in file
   deleteFile.seekg( ( partNumber - 1 ) * sizeof( Product ) );

   // read record from file
   Product prod;
   deleteFile.read( reinterpret_cast< char * >( &prod ), 
      sizeof(Product ) );

   // delete record, if record exists in file
   if ( prod.getPartNumber() != 0 ) 
   {
      Product blankPart; // create blank record

      // move file-position pointer to correct record in file
      deleteFile.seekp( ( partNumber - 1 ) * 
         sizeof( Product ) );

      // replace existing record with blank record
      deleteFile.write( 
         reinterpret_cast< const char * >( &blankPart ), 
         sizeof(Product) );

      cout << "Part #" << partNumber-1 << " deleted.\n";
   } // end if
   else // display error if record does not exist
      cerr << "Part #" << partNumber-1 << " is empty.\n";
}

void displayRecord( fstream& displayFile)
{
	cout << left << setw( 11 ) << "Record#" << setw( 30 )
		   << "HardwareData name" << setw( 13 ) << "Quantity" << left
		   << setw( 1 ) << right << "Cost" << endl;

	displayFile.seekg(0);
	Product prod;

	displayFile.read( reinterpret_cast< char * >( &prod ), sizeof( Product ) );

	while ( displayFile && !displayFile.eof() ) 
	{

		if ( prod.getPartNumber()!= 0 )
			  outputLine( cout, prod );


		   displayFile.read( reinterpret_cast< char * >( &prod ), sizeof( Product ) );
	}
	displayFile.clear();
	cout<<endl;
}
void outputLine( ostream& output, const Product &  part)
{
	output << left << setw( 11 ) << part.getPartNumber()-1
      << setw( 30 ) << part.getToolName()
      << setw( 13 ) << part.getQuantity()
      << setw( 1 ) << setprecision( 2 ) << right << fixed 
	  << showpoint << part.getCost() << endl;
}
int getPartNumber( const char * const prompt)
{
	int partNumber;

   // obtain account-number value
   do 
   {
      cout << prompt << " (0 - 99, -1 to end input): ";
      cin >> partNumber;
	  partNumber++;
   } while (( partNumber < 1 || partNumber > 100 ) && (partNumber!=0));

   return partNumber;
}
