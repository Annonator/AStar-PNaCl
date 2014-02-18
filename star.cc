#include "ppapi/cpp/instance.h"
#include "ppapi/cpp/module.h"
#include "ppapi/cpp/var.h"
#include <string>
#include <vector>
#include "json/json.h"

#include "AStar.h"
#include "Node.h"
#include "AStarWrapper.h"
#include "NodeWrapper.h"

/// The Instance class.  One of these exists for each instance of your NaCl
/// module on the web page.  The browser will ask the Module object to create
/// a new Instance for each occurrence of the <embed> tag that has these
/// attributes:
///     src="hello_tutorial.nmf"
///     type="application/x-pnacl"
/// To communicate with the browser, you must override HandleMessage() to
/// receive messages from the browser, and use PostMessage() to send messages
/// back to the browser.  Note that this interface is asynchronous.
class StarInstance : public pp::Instance {
public:
  /// The constructor creates the plugin-side instance.
  /// @param[in] instance the handle to the browser-side plugin instance.
  explicit StarInstance(PP_Instance instance) : pp::Instance(instance){
    m_star = new AStarWrapper();
  }
  virtual ~StarInstance() {
    delete m_star;
  }

  /// Handler for messages coming in from the browser via postMessage().  The
  /// @a var_message can contain be any pp:Var type; for example int, string
  /// Array or Dictinary. Please see the pp:Var documentation for more details.
  /// @param[in] var_message The message posted by the browser.
  virtual void HandleMessage(const pp::Var& var_message) {
    if(!var_message.is_string()){
      return;
    }

    std::string message = var_message.AsString();

    Json::Value root;
    Json::Reader reader;

    bool parsCheck = reader.parse(message, root);

    if (!parsCheck) {
      PostMessage(pp::Var("error"));
    }

    string command = root.get("command", "false").asString();

    if(command == "setNodes"){
      Json::Value knoten = root["nodes"];
      int x = 0;
      int y = 0;

      for (unsigned int i = 0; i < knoten.size(); ++i) {
        x = knoten[i].get("x", 0).asInt();
        y = knoten[i].get("y", 0).asInt();

        NodeWrapper* tests = new NodeWrapper(i, x, y);

        m_sammlung.push_back((Node*) tests);
      }

    }else if(command == "setConnections"){
      Json::Value knoten = root["nodes"];
      Json::Value tmp = NULL;

      for (unsigned int i = 0; i < knoten.size(); ++i) {
        tmp = knoten[i];
        for(unsigned int j = 0; j < tmp.size(); ++j){
          m_sammlung[i]->connectWith(m_sammlung[tmp[j].asInt()]);
        }
      }
    }else if(command == "solve"){
      Json::Value knoten = root["nodes"];

      if(knoten.size() == 2){

        m_star->solve(m_sammlung[knoten[0].asInt()], m_sammlung[knoten[1].asInt()]);

        PostMessage(pp::Var(m_star->toString()));

      }

    }else if(command == "resetNodes"){
      int size = m_sammlung.size();

      for(int i = 0; i<size; ++i){
        m_sammlung[i]->reset(false);
      }

    }else if(command == "resetConnections"){
      m_sammlung.clear();
    }
  }
private:
  AStarWrapper* m_star;
  vector<Node*> m_sammlung;
};

/// The Module class.  The browser calls the CreateInstance() method to create
/// an instance of your NaCl module on the web page.  The browser creates a new
/// instance for each <embed> tag with type="application/x-pnacl".
class StarModule : public pp::Module {
public:
  StarModule() : pp::Module() {}
  virtual ~StarModule() {}

  /// Create and return a HelloTutorialInstance object.
  /// @param[in] instance The browser-side instance.
  /// @return the plugin-side instance.
  virtual pp::Instance* CreateInstance(PP_Instance instance) {
    return new StarInstance(instance);
  }
};

namespace pp {
/// Factory function called by the browser when the module is first loaded.
/// The browser keeps a singleton of this module.  It calls the
/// CreateInstance() method on the object you return to make instances.  There
/// is one instance per <embed> tag on the page.  This is the main binding
/// point for your NaCl module with the browser.
  Module* CreateModule() {
    return new StarModule();
  }
}  // namespace pp
