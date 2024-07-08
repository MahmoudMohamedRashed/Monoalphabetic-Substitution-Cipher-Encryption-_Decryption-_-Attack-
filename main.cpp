#include <iostream>
#include <string>
#include <fstream>

using namespace std;
/****** ENCRYPTION *****/
string text_encription( string plain ){
    string key ="VHZRPLQOYGMEAUCWDJXKSIBTFN" ;
    string cipher;
    for( int i = 0 ; i < plain.size() ; i++ )
        if( plain[ i ] >= 'a' && plain[ i ] <= 'z' || plain[ i ] >= 'A' && plain[ i ] <= 'Z' ){
            if( plain[ i ] >= 'A' && plain[ i ] <= 'Z')plain[ i ] += 32 ;
            cipher += key[ plain[ i ] - 'a' ] ;
        }
    return cipher;
}
/*********************/

/****** DECRYPTION ****/
string text_decription( string cipher ){
    string key ="mwoqlyjbvrtfkzhegduxnapsic" ;
    string plain;
    for( int i = 0 ; i < cipher.size() ; i++ ) plain += key[ cipher[ i ] - 'A' ] ;
    return plain;
}
/*********************/

/****** ATTACK ******/
string text_attack( string cipher ){
    /***** mono_freq ****/
    int freq[ 26 ] = { 0 };
    string key = "etaoinsrhldcumfpgwybvkxjqz";
    for( int i = 0 ; i < cipher.size() ; i++ ) freq[ cipher[ i ] - 'A' ] ++ ;
    for( int i = 0 ; i < 26 ; i++ ){
        int Max = 0 ;
        for( int j = 1 ; j < 26 ; j++ ) if( freq[ j ] > freq[ Max ] )Max = j ;
        freq[ Max ] = 0 ;
        key[ i ] = ('A' + Max) ;
    }
    /*******************/
    int Bi_freq[ 26 ][ 26 ] = { 0 };
    int p1 = 0; int p2 = 1 ;
    while( p2 < cipher.size() ){
        Bi_freq [cipher[ p1 ] - 'A' ][ cipher[ p2 ] - 'A' ] ++ ;
        p2++ ;
        p1++ ;
    }
    string most_freq_bi[ 10 ] ;
    int in1 = 0 ; int in2 = 0 ;
    for(int k = 0 ; k < 10 ; k++ ){
    for( int i = 0 ; i < 26 ; i++ )
        for( int j = 0 ; j < 26 ; j++)
        if( Bi_freq[ i ][ j ] > Bi_freq[ in1 ][ in2 ]){
            in1 = i ; in2 = j ;
        }
        most_freq_bi[ k ] += (in1 +'A') ;
        most_freq_bi[ k ] += (in2 +'A') ;
        Bi_freq[ in1 ][ in2 ] = 0 ;
    }
    /*****************/
    /*****************/
    int Tri_freq[ 26 ][ 26 ][ 26 ] = { 0 };
    p1 = 0; p2 = 1 ; int p3 = 2 ;
    while( p3 < cipher.size() ){
        Tri_freq [cipher[ p1 ] - 'A' ][ cipher[ p2 ] - 'A' ][ cipher[ p3 ] - 'A' ] ++ ;
        p3++ ;
        p2++ ;
        p1++ ;
    }
    string most_freq_tri[ 5 ] ;
    in1 = 0 ; in2 = 0 ; int in3 = 0 ;
    for(int k = 0 ; k < 10 ; k++ ){
    for( int i = 0 ; i < 26 ; i++ )
        for( int j = 0 ; j < 26 ; j++)
            for( int l = 0 ; l < 26 ; l++ )
        if( Tri_freq[ i ][ j ][ l ] > Tri_freq[ in1 ][ in2 ][ in3 ]){
            in1 = i ; in2 = j ; in3 = l ;
        }
        most_freq_tri[ k ] += (in1 +'A') ;
        most_freq_tri[ k ] += (in2 +'A') ;
        most_freq_tri[ k ] += (in3 +'A') ;
        Tri_freq[ in1 ][ in2 ][ in3 ] = 0 ;
    }
    /*****************/
    string frequncies ;
    frequncies += "mono_freq : \n" ;
    for( int i = 0  ; i < 26 ; i++ ){
        frequncies += key[ i ] ;
        frequncies += ' ' ;
    }
    frequncies += "\ntop 10 Bi freq :\n" ;
    for( int i = 0 ; i < 10 ;i++ ){
        frequncies += most_freq_bi[ i ] ;
        frequncies += ' ' ;
    }
    frequncies += "\ntop 5 Tri freq :\n" ;
    for( int i = 0 ; i < 5 ; i++ ){
        frequncies += most_freq_tri[ i ] ;
        frequncies += " ";
    }
    /****************/
    string text = cipher ;
    while( 1 ){
        cout<<frequncies ;
        cout<<"\n\n\nthe cipher : \n"<<cipher<<endl ;
        cout<<"\n\n\nthe text : \n"<<text<<endl ;
        cout<<"\n\n\n" ;
        cout<<"replace letters ? : " ;
        char c1 ;
        char c2 ;
        cin>>c1>>c2;
        if( c1 == '0' || c2 == '0' )break ;
        cout<<"\n\n\n";
        for( int i = 0 ; i < text.size() ; i++ ){
                if( cipher[ i ] == ( c1 - 32 ) || cipher[ i ] == c1 ) text[ i ]= c2 ;
        }
    }
    return text ;
}
/*******************/
int main()
{
    while( 1 ){
    char state ;
    cout<<"E ( Encrypt ) , D( Decrypt ) and A ( Attack ) : " ;
    cin >> state ;
    if( state != 'A' && state != 'D' && state != 'E' ) {
        cout<<"\nEnding program" ;
        break ;
    }
    string if_name , of_name;
    cout<<"Input File name : " ;
    cin >> if_name ;
    ifstream input( if_name ) ;
    string in_txt;
    char ch ;
    while( input.get(ch) ) in_txt += ch ;
    cout<<"Output File name : " ;
    cin >> of_name ;
    string result ;
    cout<<"\n\n" ;
    switch( state ){
        case 'E' :
            result = text_encription( in_txt ) ;
            break ;
        case 'D' :
            result = text_decription( in_txt ) ;
            break ;
        case 'A' :
            result = text_attack( in_txt ) ;
            break ;
    }
    ofstream output( of_name ) ;
    for( int i = 0 ; i < result.size() ; i++ )
        output.put( result[ i ] ) ;
}
    return 0;
}
