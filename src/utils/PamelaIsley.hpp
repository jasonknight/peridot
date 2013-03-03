#ifndef PERIDOT_PAMELA_ISLEY
#define PERIDOT_PAMELA_ISLEY
/**
 * Pamela Lillian Isley AKA Poison Ivy is a Tree representation. Get it? Hahahaha.
 * */
#include "Types.hpp"
#include "Utils.hpp"
namespace Peridot {
    template <class T>
    class PamelaIsley {
        public:
            //ctor
            PamelaIsley() {
                sentinel_ = new Peridot::Node<T>(); 
                Peridot::Utils::Nil(sentinel_,"PamelaIsley.ctor"); 
                root_ = sentinel_;
                current_ = root_;
                x_ = 0;
                y_ = 0;
            }
            //dtor
            ~PamelaIsley() {
                delete sentinel_;
            }
            Peridot::Node<T> * sentinel_;
            Peridot::Node<T> * root_;
            Peridot::Node<T> * current_;
            Peridot::Node<T> * saved_;
            int                x_; // this is only used for plotting
            int                y_;
            
            // Create and delete Nodes
            Peridot::Node<T> * CreateNode(T contents) {
                Peridot::Node<T> * n = new Peridot::Node<T>();
                Peridot::Utils::Nil(n,"PamelaIsley.CreateNode");
                n->SetContents(contents).SetLeft(sentinel_).SetRight(sentinel_).SetParent(sentinel_).SetDown(sentinel_);
                assert(n->GetLeft() == sentinel_);
                return n;
            }
            void DeleteNode(Node<T> * n) { delete n;}
            
            PamelaIsley& SetRoot(Peridot::Node<T> * n) { root_ = n; return *this;}
            // This is so that we can move about in the tree, then jump back to a start
            // position by "remembering" the starting node
            PamelaIsley& SetCurrent(Peridot::Node<T> * n) { current_ = n; return *this;}

            // Here we can "remember" the current position and restore it
            PamelaIsley& Save() { saved_ = current_;return *this;}
            PamelaIsley& Restore() {current_ = saved_; return *this;}

            PamelaIsley& Insert(T contents, bool rside = true) {
               Peridot::Node<T> * n = CreateNode(contents);
               Peridot::Utils::Nil(n,"PamelaIsley->Insert");
               Peridot::Utils::Nil(current_,"PamelaIsley->Insert.current_");
               if (rside) {
                current_->SetRight(n);
                y_++;
                x_++;
               } else {
                current_->SetLeft(n);
                y_++;
                x_--;
               }
               n->SetParent(current_);
               current_ = n;
               return *this;
            } 
            PamelaIsley& InsertDown(T contents) {
               Peridot::Node<T> * n = CreateNode(contents);
               Peridot::Utils::Nil(n,"PamelaIsley->Insert");
               Peridot::Utils::Nil(current_,"PamelaIsley->Insert.current_");
               n->SetParent(current_);
               current_->SetDown(n);
               current_ = n;
               y_++;
               return *this;
            }
            PamelaIsley& InsertSimpleNode(T p,T l, T r) {
                InsertDown(p);
                Insert(l,false);
                UpRight();
                Insert(r,true);
                UpLeft();
                return *this;
            }
            Peridot::Node<T> * GetCurrent() { return current_;}
            PamelaIsley& Up() {
                current_ = current_->parent_;
                y_--;
                return *this;
            }
            PamelaIsley& UpRight() {
                current_ = current_->parent_;
                y_--;
                x_++;
                return *this;
            }
            PamelaIsley& UpLeft() {
                current_ = current_->parent_;
                y_--;
                x_--;
                return *this;
            }
            PamelaIsley& Down() {
                current_ = current_->next_;
                y_++;
                return *this;
            }
            PamelaIsley& Right() {
                current_ = current_->right_;
                x_++;
                return *this;
            }
            PamelaIsley& Left() {
                current_ = current_->left_;
                x_--;
                return *this;
            }
            //PamelaIsley& Draw(Peridot::Node<T> * c) {
            //    int i = 0;
            //    while (i < 39) {
            //        i++;
            //        std::cout << " ";
            //    }
            //    std::cout << c->ToString() << std::endl;
            //    if (current_->GetLeft() != sentinel_) {
            //        DrawNode(c->GetLeft(),1, true);
            //    }                
            //    if (current_->GetRight() != sentinel_) {
            //        DrawNode(c->GetRight(),1, false);
            //    }
            //    if (c->GetDown() != sentinel_) {
            //        std::cout << std::endl;
            //        Draw(c->GetDown());
            //    }
            //    return *this; 
            //}
            //void DrawNode(Peridot::Node<T> * n, int level,bool l = false) {
            //    int num_spaces = 40 - level;
            //    if (l) {
            //        num_spaces -= 5;
            //    } else {
            //        num_spaces = 10;
            //    }
            //    DrawBlankSpaces(num_spaces); 
            //    std::cout << n->ToString();
            //    if (l == false)
            //        std::cout << std::endl;
            //    if (n->GetLeft() != sentinel_) {
            //        DrawNode(n->GetLeft(),level + 1, true);
            //    }            
            //    if (n->GetRight() != sentinel_) {
            //        DrawNode(n->GetRight(),level + 1, false);
            //    }
            //}
            //void DrawBlankSpaces(int spaces) {
            //    int i = 0;
            //    while (i < spaces) {
            //        i++;
            //        std::cout << " ";
            //    }
            //}

    }; // End Class PamelaIsley
} // End Namespace Peridot
#endif
