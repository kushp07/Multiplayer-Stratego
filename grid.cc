#include "grid.h"
#include "ability.h"
#include "exception.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

Grid::Grid(bool graphics): graphics{graphics} {}

Grid::~Grid() {
	delete player1;
	delete player2;
	delete td;
	delete ob;
}

void Grid::setObserver(GraphicsDisplay *ob) {
	this->ob = ob;
}

int Grid::getTurn(){
        return player;
}

int Grid::whoWon() {
	if (player1->getInfo().downloadedviruses == 4) {
		return 2;
	} else if (player1->getInfo().downloadeddata == 4) {
		return 1;
	} else if (player2->getInfo().downloadedviruses == 4) {
		return 1;
	} else if (player2->getInfo().downloadeddata == 4) {
		return 2;
	} else {
		return 0;
	}
}


size_t charToInt(char c) {
	string s;
	s += c;
	size_t n;
	istringstream ss{s};
	ss >> n;
	return n;
}

char incrementCharacter(char c, int i) {
	char temp = c + i;
	char s;
	s += temp;
	return s;
}


void Grid::init(size_t n, vector<string> p1order, vector<string> p2order, 
		vector<char> p1abilities, vector<char> p2abilities) {
	width = n;
	height = n;
	// Set Display
	delete td;
	td = new TextDisplay(n);
	// Populating Grid with empty Cells
	for (size_t i = 1; i <= height; ++i) {
		vector<Cell> row;
		for (size_t j = 1; j <= width; ++j) {
			// Setting up Sever Ports
			if(((i == 1) && ((j == 4) || (j == 5))) || ((i == 8) && ((j == 4) || (j == 5)))) {
				Cell current = Cell(i,j,true);
				current.attach(td);
				if (graphics) {
					current.attach(ob);
				}
				row.emplace_back(current);
			}
			else {
				Cell current = Cell(i,j);
				current.attach(td);
				if (graphics) {
					current.attach(ob);
				}
				row.emplace_back(current);
			}
		}
		theGrid.emplace_back(row);	
	}
	// Intializing p1 board
	vector<Link*> p1downloaded;
	vector<Link*> p1owns;
	size_t one = 1;
	size_t zero = 0;
	for (size_t i = 0; i < 8; ++i) {
		string current = p1order.at(i);
		Link* currentLink = nullptr;
		size_t strength = charToInt(current[1]);
		char c = incrementCharacter('a', i);
		if (current[0] == 'V') {
			if (i == 3 || i == 4) {
				currentLink = new Virus(one, i, one, strength, c);
				theGrid[1][i].setLink(currentLink);
			}  else {
				currentLink = new Virus(zero, i, one, strength, c);
				theGrid[0][i].setLink(currentLink);
			}
		} else if (current[0] == 'D') {
			if (i == 3 || i == 4) {
				currentLink = new Data(one, i , one, strength, c);
				theGrid[1][i].setLink(currentLink);
			} else {
				currentLink = new Data(zero, i, one, strength, c);
				theGrid[0][i].setLink(currentLink);
			}
		}
		p1owns.emplace_back(currentLink);
	}
	player1 = new Player(p1downloaded, p1owns, p1abilities, p1order, 1);
	player1->attach(td);
	if (graphics) {
		player1->attach(ob);
	}
	player1->notifyObservers(true);

	// Intializing p2 board
	vector<Link*> p2downloaded;
        vector<Link*> p2owns;
	size_t six = 6;
	size_t seven = 7;
	size_t two = 2;
        for (size_t i = 0; i < 8; ++i) {
                string current = p2order.at(i);
                Link *currentLink = nullptr;
                size_t strength = charToInt(current[1]);
                char c = incrementCharacter('A', i);
                if (current[0] == 'V') {
                        if (i == 3 || i == 4) {
                                currentLink = new Virus(six, i, two, strength, c);
                                theGrid[6][i].setLink(currentLink);
                        }  else {
                                currentLink = new Virus(seven, i, two, strength, c);
                                theGrid[7][i].setLink(currentLink);
                        }
                } else if (current[0] == 'D') {
                        if (i == 3 || i == 4) {
                                currentLink = new Data(six, i, two, strength, c);
                                theGrid[6][i].setLink(currentLink);
                        } else {
                                currentLink = new Data(seven, i, two, strength, c);
                                theGrid[7][i].setLink(currentLink);
                        }
                }
                p2owns.emplace_back(currentLink);
	}
	player2 = new Player(p2downloaded, p2owns, p2abilities, p2order, 2);
	player2->attach(td);
	if (graphics) {
		player2->attach(ob);
	}
	player2->notifyObservers(true);
}


bool Grid::invalidMove(string dir, int index, int moves) {
	bool invalidmove = false;
	int i;
	int j;
	string invalmove1 = "\n*Invalid move: can only move up, down, left and right*\n";
	string invalmove2 = "\n*Invalid move: cannot move onto your server port*\n";
	string invalmove3 = "\n*Invalid move: cannot move off board*\n";
	string invalmove4 = "\n*Invalid move: cannot move on existing piece*\n";
	string invalmove5 = "\n*Invalid move: cannot move a trapped piece *\n";
//	string invalmove6 = "\n*Oh no! You've stepped into a secret trap placed by your opponent. You are unable to move this piece now *\n";

	if(player == 1) {
		i = player1->getowns().at(index)->getInfo().col;
                j = player1->getowns().at(index)->getInfo().row;
		if(theGrid[j][i].istrap(2)) {
			throw Exception(invalmove5);
		}
                if(dir == "up") {
			j -= moves;
                } else if(dir == "down") {
                        j += moves;
                } else if(dir == "right") {
                        i += moves;
                } else if(dir == "left") {
                        i -= moves;
		} else {
			throw Exception(invalmove1);
			invalidmove = true;
		}
		if((invalidmove == false) && ((j == 0) && ((i == 3) || (i == 4)))) {
			throw Exception(invalmove2);
			invalidmove = true;
		}
		else if((invalidmove == false) && ((i < 0) || (i > 7) || (j < 0))) {
			throw Exception(invalmove3);
                        invalidmove = true;
		}
		else if (invalidmove == false) {
			for(size_t n = 0; n < player1->getowns().size(); ++n) {
				if((n != index) && ((player1->getowns().at(n)->getInfo().row) == j) && ((player1->getowns().at(n)->getInfo().col) == i)) {
					throw Exception(invalmove4);
                                	invalidmove = true;
				}
			}
		}
	}
	else if(player == 2) {
                i = player2->getowns().at(index)->getInfo().col;
                j = player2->getowns().at(index)->getInfo().row;
                if(theGrid[j][i].istrap(1)) {
                        throw Exception(invalmove5);
                }
		if(dir == "up") {
                        j -= 1;
                } else if(dir == "down") {
                        j += 1;
                } else if(dir == "right") {
                        i += 1;
                } else if(dir == "left") {
                        i -=1;
                } else {
                        throw Exception(invalmove1);
                        invalidmove = true;
		}
		if((invalidmove == false) && ((j == 7) && ((i == 3) || (i == 4)))) {
			throw Exception(invalmove2);
                        invalidmove = true;
                }
                else if((invalidmove == false) && ((i < 0) || (i > 7) || (j > 7))) {
                        throw Exception(invalmove3);
                        invalidmove = true;
                }

                else if (invalidmove == false) {
                        for(size_t n = 0; n < player2->getowns().size(); ++n) {
                                if((n != index) && ((player2->getowns().at(n)->getInfo().row == j) && ((player2->getowns().at(n)->getInfo().col) == i))) {
                                        throw Exception(invalmove4);
                                        invalidmove = true;
                                }
                        }
                }
        }
	return invalidmove;
}


void Grid::move(char link, string dir) { 
	int index;
	bool index_set = false;
	bool onserver = false;
	int moves = 1;
	string invalLink = "\nInvalid Link";
	string linkNotOwned = "\n*Link does not belong to player 1*\n"; 
	string linkNotOwned2 = "\n*Link does not belong to player 2*\n"; 
//	string intrap = "\n*Oh no! You've stepped into a secret trap placed by your opponent. You are unable to move this piece now *\n";
		for (size_t i = 0; i < player1->getdownloaded().size(); ++i)  {
			if ((player1->getdownloaded().at(i)->getInfo().name) == link) {
				throw Exception(invalLink);
			}
		}
		for (size_t i = 0; i < player2->getdownloaded().size(); ++i)  {
				if ((player2->getdownloaded().at(i)->getInfo().name) == link) {
					throw Exception(invalLink);
				}
			}
				 
	if(player == 1) {
		//finding link in owns vector
		for(size_t i = 0; i < player1->getowns().size(); ++i) {
			if((player1->getowns().at(i)->getInfo().name) == link) {
				index = i;
				index_set = true;
				break;
			}
		} if(!index_set) { 
			throw Exception(linkNotOwned); 
		} if(player1->getowns().at(index)->getInfo().boosted) {
                       moves = 2;
		} if(!(invalidMove(dir,index, moves))) {
			td->setTurn(2);
			if (graphics) {
				ob->setTurn(2);
			}
			int i = player1->getowns().at(index)->getInfo().col;
			int j = player1->getowns().at(index)->getInfo().row;
			theGrid[j][i].setLink(nullptr);
			
			if(dir == "up") {
                        	j -= moves;
			} else if(dir == "down") {
                        	j += moves;
                	} else if(dir == "right") {
                        	i += moves;
                	} else if(dir == "left") {
                        	i -= moves;
			}
			// moving off edge of oponents side
			if(j > 7) {
				Link *temp = player1->getowns().at(index);
				player1->downloadLink(temp);
				onserver = true;
			}
			// moving into opponents server ports
			else if((j == 7) && ((i == 3) || (i == 4))) {
				Link *temp = player1->getowns().at(index);
                                player2->downloadLink(temp);
								player1->notifyObservers(true);
							
				onserver = true;
			} // Checking firewall
			 else if(theGrid[j][i].isfirewall(2)) {
			 	if (player1->getowns().at(index)->getInfo().isVirus) {
	   				Link *temp = player1->getowns().at(index);
					player1->downloadLink(temp);
					onserver = true;
       				}
				player1->getowns().at(index)->reveal(); 
				player1->notifyObservers(false);
			} else if(theGrid[j][i].istrap(2)) {
				cout << "\nOh no! You've stepped into a secret trap placed by your opponent. You are unable to move this piece now\n" << endl;
			}
			else {
				// initiating battle
				for(size_t n = 0; n < player2->getowns().size(); ++n) {
					if(((player2->getowns().at(n)->getInfo().row) == j) && ((player2->getowns().at(n)->getInfo().col) == i)) {
						if((player2->getowns().at(n)->getInfo().strength) > (player1->getowns().at(index)->getInfo().strength)) {
							Link *temp = player1->getowns().at(index);
											   player2->getowns().at(n)->reveal();
                               				player2->downloadLink(temp);
											   player1->notifyObservers(true);
											   onserver = true;
						} else {
							Link *temp = player2->getowns().at(n);
											player1->getowns().at(index)->reveal();
                                			player1->downloadLink(temp);
											player2->notifyObservers(true);

						}	
						break;
					}

				}
			}		

			if(!onserver) {
							player1->getowns().at(index)->setcol(i);
			player1->getowns().at(index)->setrow(j);
				theGrid[j][i].setLink(player1->getowns().at(index));
				onserver = false;
			} 
		}
		player = 2;
	} 
	else if(player == 2) {	
                //finding link in owns vector
                for(size_t i = 0; i < player2->getowns().size(); ++i) {
                        if((player2->getowns().at(i)->getInfo().name) == link) {
                                index = i;
                                index_set = true;
                                break;
                        }
                } if(!index_set) {
                        throw Exception(linkNotOwned2);
                }
		if(player2->getowns().at(index)->getInfo().boosted) {
                       moves = 2;
                }
                if(!invalidMove(dir,index, moves)) {
                        td->setTurn(1);
			if (graphics) {
				ob->setTurn(1);
			}
		       	int i = player2->getowns().at(index)->getInfo().col;
                        int j = player2->getowns().at(index)->getInfo().row;
                        theGrid[j][i].setLink(nullptr);
			
			if(dir == "up") {
                                j -= moves;
                        } else if(dir == "down") {
                                j += moves;
                        } else if(dir == "right") {
                                i += moves;
                        } else if(dir == "left") {
                                i -= moves;
                        }
                        // moving off edge of oponents side
                        if(j < 0) {
                                Link *temp = player2->getowns().at(index);
                                player2->downloadLink(temp);
								onserver = true;
                        }
                        // moving into opponents server ports
                        else if((j == 0) && ((i == 3) || (i == 4))) {
                                Link *temp = player2->getowns().at(index);

                                player1->downloadLink(temp);
								player2->notifyObservers(true);
				onserver = true;
                        } // Checking firewall
			else if(theGrid[j][i].isfirewall(1)) {
				if (player2->getowns().at(index)->getInfo().isVirus) {
					Link *temp = player2->getowns().at(index);
					player2->downloadLink(temp);
					onserver = true;
				}
				player2->getowns().at(index)->reveal();
				player2->notifyObservers(false);
						 
			}
			else if(theGrid[j][i].istrap(1)) {
                                cout << "\nOh no! You've stepped into a secret trap placed by your opponent. You are unable to move this piece now\n" << endl;
                        }
			else {
	 			// intiating battle
				for(size_t n = 0; n < player1->getowns().size(); ++n) {
				       	if(((player1->getowns().at(n)->getInfo().row) == j) && ((player1->getowns().at(n)->getInfo().col) == i)) {
						if((player1->getowns().at(n)->getInfo().strength) > (player2->getowns().at(index)->getInfo().strength)) {
							Link *temp = player2->getowns().at(index);
							player1->getowns().at(n)->reveal();
							player1->downloadLink(temp);
							player2->notifyObservers(true);
							onserver = true;
						} else {
	  						Link *temp = player1->getowns().at(n);
							  player2->getowns().at(index)->reveal();
		  					player2->downloadLink(temp);
							player1->notifyObservers(true);
                                               
			  			}
					}
				}
			}

			if(!onserver) {
				player2->getowns().at(index)->setcol(i);
                        	player2->getowns().at(index)->setrow(j);
                                theGrid[j][i].setLink(player2->getowns().at(index));
				onserver = false;
                        
			}
		}
		player = 1;
	}
}

string Grid::abilities(){
	Player *play = nullptr;
	if(player == 1) {
		play = player1;
	} else if(player == 2){
		play = player2;
	}
	string abilitiesList;
	for(size_t i = 0; i < play->getabilities().size(); ++i) {
		char current = play->getabilities()[i];
		char index = '1';
		index += i;
		abilitiesList += index;
		string abilityI;
		if(current== 'L') {
			abilityI = "Link Boost";
		} else if (current == 'F') {
			abilityI = "Firewall";
		} else if (current == 'D') {
			abilityI = "Download";
		} else if (current == 'P') {
			abilityI = "Polarize";
		} else if (current == 'S') {
			abilityI = "Scan";
		} else if (current == 'E') {
			abilityI = "Extra Strength";
		} else if (current == 'W') {
			abilityI = "Wild Card";
		} else if (current == 'T') {
			abilityI = "Trap!";
		} 
		abilitiesList = abilitiesList + ": " + abilityI + "  "; 
	}
	return abilitiesList;
}

void Grid::ability(size_t which, std::istream &in){
	Player *play = nullptr;
	string invalAbility = "\n*Invalid Ability*\n";
	if(player == 1) {
		play = player1;
	} else if(player == 2){
		play = player2;
	}
	if((which > play->getabilities().size()) || (which == 0)) {
		throw Exception(invalAbility);
	}else{
		if (play->getabilities()[which-1] == 'L'){
			char link;
			if (in >> link) linkboost(link);
			else throw Exception("\n*Invalid Input*\n");
		} else if (play->getabilities()[which - 1] == 'S'){
			char link;
			if (in >> link) scan(link);
			else throw Exception("\n*Invalid Input*\n");
		} else if (play->getabilities()[which-1] == 'P'){
			char link;
			if (in >> link) polarize(link);
			else throw Exception("\n*Invalid Input*\n");
		} else if (play->getabilities()[which-1] == 'D'){
			char link;
			if (in >> link) download(link);
			else throw Exception("\n*Invalid Input*\n");
		} else if (play->getabilities()[which-1] == 'F'){
			int row;
			int col;
			if (in >> row){}
			else throw Exception("\n*Invalid Input*\n");
			if (in >> col) firewall(row,col);
			else throw Exception("\n*Invalid Input*\n"); 
		} else if (play->getabilities()[which-1] == 'W'){
			char newAbility;
			if (in >> newAbility) wildcard(newAbility);
			else throw Exception("\n*Invalid Input*\n");
		}else if (play->getabilities()[which-1] == 'E'){
			char link;
			if (in >> link) extrastrength(link);
			else throw Exception("\n*Invalid Input*\n");
		}else if (play->getabilities()[which-1] == 'T'){
			int row;
			int col;
			if (in >> row){}
			else throw Exception("\n*Invalid Input*\n");
			if (in >> col) trap(row,col);
			else throw Exception("\n*Invalid Input*\n");
		}
	}
	play->removeability(which - 1);
}

void Grid::linkboost(char link){
        Player *play = nullptr;
        if (player == 1){
                play = player1;
        }else if (player == 2){
                play = player2;
        }
        bool found = false;
        for(size_t i = 0; i < play->getowns().size(); ++i) {
                if ((play->getowns().at(i)->getInfo().name) == link){
                        found = true;
                        play->getowns().at(i)->setboosted(true);
                        break;
                }
        }
        if (!found){
                throw Exception("\n*Invalid Link*");
        }
        play->notifyObservers(true);
}

void Grid::scan(char link){
        Player *play = nullptr;
        if (player == 1){
                play = player2;
        }else if (player == 2){
                play = player1;
        }
	bool found = false;
        for(size_t i = 0; i < play->getowns().size(); ++i) {
                if ((play->getowns().at(i)->getInfo().name) == link){
			found = true;
                        play->getowns().at(i)->reveal();
                        break;
                }
        }
	if (!found){
		throw Exception("\n*Invalid Link*");
	}
	play->notifyObservers(true);
}
void Grid::polarize(char link){
 	Player *play = nullptr;
        Link *newLink = nullptr;
        int index;
        if (player == 1){
                play = player1;
        }else if (player == 2){
                play = player2;
        }
	bool found = false;
        for(size_t i = 0; i < play->getowns().size(); ++i) {
                if ((play->getowns().at(i)->getInfo().name) == link){
			play->getowns().at(i)->setswitched(!play->getowns().at(i)->getInfo().switched);
			found = true;
			index = i;
			break;
                }
        }
	if (!found){
		throw Exception("\n*Invalid Link*");
	}
	char t = play->getorder().at(index)[0];
	char s = play->getorder().at(index)[1];
	if (t == 'V') {
		string add;
		add += 'D';
		add += s;
		play->getorder()[index] = add;
	} else if (t == 'D') {
		string add;
		add += 'V';
		add += s;
		play->getorder()[index] = add;
	}
}

void Grid::download(char link){
	int index;
	Link *temp = nullptr;
	string invalLink = "\nInvalid Link";
	bool found = false;
	for (size_t i = 0; i < player1->getdownloaded().size(); ++i)  {
			if ((player1->getdownloaded().at(i)->getInfo().name) == link) {
				throw Exception(invalLink);
			}
		}
		for (size_t i = 0; i < player2->getdownloaded().size(); ++i)  {
					 if ((player2->getdownloaded().at(i)->getInfo().name) == link) {
						 throw Exception(invalLink);
					 }
				}
 	if(player == 1) {
		 		
                for(size_t i = 0; i < player2->getowns().size(); ++i) {
                        if((player2->getowns().at(i)->getInfo().name) == link) {
				found = true;
                                index = i;
                                break;
                        }
                }
				if (!found){
		throw Exception(invalLink);
	}
                temp = player2->getowns().at(index);
		theGrid[temp->getInfo().row][temp->getInfo().col].setLink(nullptr);
                player1->downloadLink(temp);
				player2->notifyObservers(true);
        }
        else if(player == 2) {
                for(size_t i = 0; i < player1->getowns().size(); ++i) {
                        if((player1->getowns().at(i)->getInfo().name) == link) {
				found = true;
                                index = i;
                                break;
                        }
                }
				if (!found){
		throw Exception(invalLink);
	}
		temp = player1->getowns().at(index);
		theGrid[temp->getInfo().row][temp->getInfo().col].setLink(nullptr);
		player2->downloadLink(temp);
		player1->notifyObservers(true);
        }

   //     theGrid[temp->getInfo().row][temp->getInfo().col].setLink(nullptr);
}

void Grid::firewall(int row, int col){
	bool error = false;
	string invalfire = "\n*Invalid Firewall Placement*\n";
	if(((row == 0) && ((col == 3) || (col == 4))) ||
	   ((row == 7) && ((col == 3) || (col == 4))) ||
	   (col < 0) || (col > 7) || (row < 0) || (row > 7)) {
		error = true;
		throw Exception(invalfire);
	} else {
		// check if player 1 has a piece on it
		for(size_t n = 0; n < player1->getowns().size(); ++n) {
			if(((player1->getowns().at(n)->getInfo().row) == row) && ((player1->getowns().at(n)->getInfo().col) == col)) {
				error = true;
				throw Exception(invalfire);				
			}
		}
	 // check if player 2 has a piece on it
                for(size_t n = 0; n < player2->getowns().size(); ++n) {                              
                        if(((player2->getowns().at(n)->getInfo().row) == row) && ((player2->getowns().at(n)->getInfo().col) == col)) {                                  
                                error = true;                                           
                                throw Exception(invalfire);                                     
                        }
                }       

	}
	if(!error) {
		theGrid[row][col].setfirewall(player,true);
	}

}

void Grid::wildcard(char newAbility) {
	string invalabil = "\n*Cannot Swap to Invalid Ability*\n";
	Player *play = nullptr;
    if (player == 1){
            play = player1;
    }else if (player == 2){
            play = player2;
    }
	string abilitiesList = "LSDFPET";
	for (int i = 0; i < abilitiesList.length(); ++i) {
		if (newAbility == abilitiesList[i]) {
			play->addability(newAbility);
			return;
		}
	}
	throw Exception(invalabil);

}

void Grid::extrastrength(char link){
	Player *play = nullptr;
        if (player == 1){
                play = player1;
        }else if (player == 2){
                play = player2;
        }
	bool found = true;
	string invalLink = "\nInvalid Link";
        for (size_t i=0; i < play->getowns().size(); ++i){
                if((play->getowns().at(i)->getInfo().name) == link){
						found = true;
                        play->getowns().at(i)->incstrength();
						char t = play->getorder().at(i)[0];
						char s = play->getorder().at(i)[1];
						s += 1;
						string add;
						add += t;
						add += s;
						play->getorder()[i] = add;
                }
        }
	if (!found){
		throw Exception(invalLink);
	}
}

void Grid::trap(int row, int col){
        bool error = false;
        string invaltrap = "\n*Invalid Trap Placement*\n";
        if(((row == 0) && ((col == 3) || (col == 4))) ||
           ((row == 7) && ((col == 3) || (col == 4))) ||
           (col < 0) || (col > 7) || (row < 0) || (row > 7)) {
                error = true;
                throw Exception(invaltrap);
        }else if ((theGrid[row][col].isfirewall(1)) || (theGrid[row][col].isfirewall(2))){
			error = true;
			throw Exception(invaltrap);
		}else if(!error) {
                // check if player 1 has a piece on it
                for(size_t n = 0; n < player1->getowns().size(); ++n) {
                        if(((player1->getowns().at(n)->getInfo().row) == row) && ((player1->getowns().at(n)->getInfo().col) == col)) {
                                error = true;
                                throw Exception(invaltrap);
                        }
                }

        }
        if(!error) {
         // check if player 2 has a piece on it
                for(size_t n = 0; n < player2->getowns().size(); ++n) {
                        if(((player2->getowns().at(n)->getInfo().row) == row) && ((player2->getowns().at(n)->getInfo().col) == col)) {
                                error = true;
                                throw Exception(invaltrap);
                        }
                }


        }
        if(!error) {
                theGrid[row][col].settrap(player,true);
        }
}

ostream &operator<<(ostream &out, const Grid&g) {
	out << *(g.td);
	return out;
}

